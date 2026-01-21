/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:27:23 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/16 16:10:08 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execve_cmd(t_ast *ast, t_shell *sh)
{
	pid_t	pid;
  char	*path;

	pid = fork();
	if (pid == 0) 
	{
		if (check_redirections(ast) == -1)
			return ;
		path = find_path(ast->args[0], sh);
		// printf("\n path == %s",path);
		// TODO: caso digitem um comando /bin/ls deve ser executado da mesma forma
		if (execve(path, ast->args, sh->envp) == -1)
		{
			ft_printf("minishell: %s: command not found\n",ast->args[0]);
			sh->exit_status = 127;
		}
	}
	waitpid(pid, &sh->exit_status, 0);
}
