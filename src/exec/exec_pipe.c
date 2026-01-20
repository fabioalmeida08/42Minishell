/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:42:29 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/05 16:21:28 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_childs(t_ast *node, int *fd, int dir, t_shell *sh)
{
	if (dir == 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_ast(node, sh);
	exit(sh->exit_status);
}

void	execute_pipe(t_ast *ast, t_shell *sh)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;

	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
		exec_childs(ast->left, fd, 1, sh);
	pid[1] = fork();
	if (pid[1] == 0)
		exec_childs(ast->right, fd, 0, sh);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		sh->exit_status = 128 + WTERMSIG(status);
}
