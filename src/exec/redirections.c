/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:15:26 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/08 15:17:56 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_heredoc(char *delimiter)
{
	int		fd;
	char	*line;
	char	*filename = "/tmp/.mshell_heredoc_tmp";

	// 1. Abre arquivo para escrita
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc open");
		return (-1);
	}
	while (1)
	{
		line = readline("> "); // Prompt secundário
		if (!line) // Trata Ctrl+D (EOF forçado)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `EOF')\n",2);
			break ;
		}
		if (ft_strcmp(line, delimiter)) // Verifica se é o delimitador
		{
			free(line);
			break ;
		}
		// AQUI entraria a expansão de variáveis no futuro
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd); // Readline remove o \n, precisamos repor
		free(line);
	}
	close(fd);
	// 2. Abre o mesmo arquivo agora apenas para leitura
	fd = open(filename, O_RDONLY);
	// 3. Unlink remove o arquivo do sistema (limpeza), mas mantém o FD aberto
	unlink(filename);
	return (fd);
}

static int	open_target(t_redirect *tmp)
{
	int	fd;

	// >>> Lógica Nova <<<
	if (tmp->type == REDIR_HEREDOC)
	{
		fd = process_heredoc(tmp->target);
	}
	// >>> Lógica Antiga <<<
	else if (tmp->type == REDIR_IN)
		fd = open(tmp->target, O_RDONLY);
	else if (tmp->type == REDIR_OUT)
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else // REDIR_APPEND
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	
	if (fd == -1 && tmp->type != REDIR_HEREDOC) // Evita duplo perror se falhar heredoc
	{
		ft_putstr_fd("minishell: ", 2);
		perror(tmp->target);
	}
	return (fd);
}

int	check_redirections(t_ast *node)
{
	t_redirect	*tmp;
	int			fd;

	tmp = node->redirs;
	while (tmp)
	{
		fd = open_target(tmp);
		if (fd == -1)
			return (-1);
		
		// >>> MUDANÇA IMPORTANTE AQUI <<<
		// Heredoc deve se comportar como Input (<) para o dup2
		if (tmp->type == REDIR_IN || tmp->type == REDIR_HEREDOC)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("minishell: dup2"), close(fd), -1);
		}
		else // OUT ou APPEND
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("minishell: dup2"), close(fd), -1);
		}
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

void	execute_builtin_with_redir(t_ast *ast, t_shell *sh)
{
	int	saved_stdout;

	// 1. Salva o STDOUT original (geralmente o terminal)
	saved_stdout = dup(STDOUT_FILENO);
	
	// 2. Tenta aplicar os redirecionamentos
	if (check_redirections(ast) == -1)
	{
		sh->exit_status = 1;
		// Restaura e sai
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		return ;
	}

	// 3. Executa o builtin (agora escrevendo no arquivo se tiver >)
	exec_builtin(ast->args, sh);

	// 4. Restaura o STDOUT original para o shell voltar ao normal
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
