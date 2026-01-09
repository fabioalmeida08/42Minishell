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

int	check_redirections(t_ast *node)
{
	t_redirect	*tmp;
	int			fd;

	tmp = node->redirs;
	while (tmp)
	{
		fd = -1;
		// --- 1. ABRE O ARQUIVO COM AS FLAGS CERTAS ---
		if (tmp->type == REDIR_IN) // Input <
		{
			// Abre APENAS para leitura. O arquivo PRECISA existir.
			fd = open(tmp->target, O_RDONLY);
		}
		else if (tmp->type == REDIR_OUT) // Output >
		{
			fd = open(tmp->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (tmp->type == REDIR_APPEND) // Append >>
		{
			fd = open(tmp->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}

		// --- 2. VERIFICA ERROS DE ABERTURA ---
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(tmp->target); // Ex: "No such file or directory"
			return (-1);
		}

		// --- 3. FAZ O DUP2 (A TROCA DE PORTAS) ---
		if (tmp->type == REDIR_IN)
		{
			// Se for Input, trocamos o STDIN (0) pelo arquivo
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("minishell: dup2");
				close(fd);
				return (-1);
			}
		}
		else // Para > e >>
		{
			// Se for Output, trocamos o STDOUT (1) pelo arquivo
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("minishell: dup2");
				close(fd);
				return (-1);
			}
		}

		close(fd); // Fecha o original, pois o dup2 já duplicou
		tmp = tmp->next;
	}
	return (0);
}
// int	check_redirections(t_ast *node)
// {
// 	t_redirect	*tmp;
// 	int			fd;
//
// 	tmp = node->redirs;
// 	while (tmp)
// 	{
// 		fd = -1;
// 		if (tmp->type == REDIR_IN) // Input <
// 		{
// 			// Abre APENAS para leitura. O arquivo PRECISA existir.
// 			fd = open(tmp->target, O_RDONLY);
// 		}
// 		if (tmp->type == REDIR_OUT) // Caso do >
// 		{
// 			// O_TRUNC = Sobrescreve
// 			// O_CREAT = Cria se não existir
// 			// O_WRONLY = Apenas escrita
// 			// 0644 = Permissões de leitura/escrita
// 			fd = open(tmp->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		}
// 		else if (tmp->type == REDIR_APPEND) // Append >>
// 		{
// 			fd = open(tmp->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		}
// 		// Aqui você adicionaria else if (tmp->type == REDIR_APPEND) ...
//
// 		if (fd == -1)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			perror(tmp->target);
// 			return (-1); // Erro ao abrir arquivo
// 		}
//
// 		// Redireciona o FD do arquivo para o STDOUT (1)
// 		if (dup2(fd, STDOUT_FILENO) == -1)
// 		{
// 			perror("minishell: dup2");
// 			close(fd);
// 			return (-1);
// 		}
// 		close(fd); // Não precisamos mais do fd original, o 1 já aponta para o arquivo
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

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
