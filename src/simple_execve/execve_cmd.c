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

void	execve_cmd(char **input, t_shell *sh)
{
	char	*path;
	pid_t	pid;

	sh->exit_status = 127;
	path = find_path(input[0], sh);
	if (!path)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		return ;
	}
	if (pid == 0)
		exec_child(path, input, sh);
	exec_parent(pid, sh);
	free(path);
}
