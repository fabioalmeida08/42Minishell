/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:15:26 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/22 10:17:34 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	restore_io(int saved_out, int saved_in)
{
	dup2(saved_out, STDOUT_FILENO);
	dup2(saved_in, STDIN_FILENO);
	close(saved_out);
	close(saved_in);
}

static int	open_target(t_redirect *tmp, t_shell *sh)
{
	int	fd;
	int	flags;

	if (tmp->type == REDIR_HEREDOC)
		return (process_heredoc(tmp->target, true, sh));
	if (tmp->type == REDIR_IN)
		flags = O_RDONLY;
	else if (tmp->type == REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(tmp->target, flags, 0644);
	if (fd == -1)
		perror(tmp->target);
	return (fd);
}

int	check_redirections(t_ast *node, t_shell *sh)
{
	t_redirect	*tmp;
	int			fd;

	tmp = node->redirs;
	while (tmp)
	{
		fd = open_target(tmp, sh);
		if (fd == -1)
			return (-1);
		if (tmp->type == REDIR_IN || tmp->type == REDIR_HEREDOC)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("Minishell: dup2 failed"), close(fd), -1);
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("Minishell: dup2 failed"), close(fd), -1);
		}
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

void	execute_builtin_with_redir(t_ast *ast, t_shell *sh)
{
	int	saved_stdout;
	int	saved_stdin;

	if (!ast->redirs)
	{
		exec_builtin(ast->args, sh);
		return ;
	}
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (check_redirections(ast, sh) == -1)
	{
		sh->exit_status = 1;
		restore_io(saved_stdout, saved_stdin);
		return ;
	}
	exec_builtin(ast->args, sh);
	restore_io(saved_stdout, saved_stdin);
}
