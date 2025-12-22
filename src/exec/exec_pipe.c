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

void execute_pipe(t_ast *ast, t_shell *sh)
{
    int     fd[2];
    pid_t   pid_left;
    pid_t   pid_right;
    int     status_right;

    pipe(fd);

    pid_left = fork();
    if (pid_left == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execute_ast(ast->left, sh);
        exit(sh->exit_status);
    }

    pid_right = fork();
    if (pid_right == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        execute_ast(ast->right, sh);
        exit(sh->exit_status);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid_left, NULL, 0);
    waitpid(pid_right, &status_right, 0);

    if (WIFEXITED(status_right))
        sh->exit_status = WEXITSTATUS(status_right);
    else if (WIFSIGNALED(status_right))
        sh->exit_status = 128 + WTERMSIG(status_right);
		printf("\nexit status do ultimo comando = %d\n",sh->exit_status);
}
