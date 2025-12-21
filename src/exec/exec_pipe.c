/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:42:29 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/16 16:24:55 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipe(t_ast *ast, t_shell *sh)
{
	(void) ast;
	(void) sh;
	int	fd[2];
	pipe(fd);

	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/ls", (char*[]){"ls", NULL}, sh->envp);
	}

	if (fork() == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve("/bin/grep", (char*[]){"grep", "c", NULL}, sh->envp);
	}

	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	//TODO: ligar o output do primeiro comando com o output do segundo
	printf("pipe exec ast-left %s %s\n",ast->right->args[0],ast->right->args[1]);

}
