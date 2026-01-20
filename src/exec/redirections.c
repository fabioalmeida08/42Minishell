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

static int	open_target(t_redirect *tmp)
{
	int	fd;

	if (tmp->type == REDIR_IN)
		fd = open(tmp->target, O_RDONLY);
	else if (tmp->type == REDIR_OUT)
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
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
		if (tmp->type == REDIR_IN)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("minishell: dup2"), close(fd), -1);
		}
		else
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
