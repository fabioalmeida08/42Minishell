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
		// 1. Aplica redirecionamentos NO FILHO
		if (check_redirections(ast) == -1)
		{
			exit(1);
		}

					// Limpa memória e sai se falhar
				// 2. Busca o caminho e executa
			path = find_path(ast->args[0], sh);
			if (execve(path, ast->args, sh->envp) == -1)
			{
					perror("execve");
			//TODO: exit é melhor opcao agora mesmo
					exit(127);
			}
	}
    // Processo Pai apenas espera
	waitpid(pid, &sh->exit_status, 0);
    // ... trata o exit status ...
}
// void	execve_cmd(char **input, t_shell *sh)
// {
// 	char	*path;
// 	pid_t	pid;
//
// 	sh->exit_status = 127;
// 	path = find_path(input[0], sh);
// 	if (!path)
// 		return ;
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		free(path);
// 		return ;
// 	}
// 	if (pid == 0)
// 		exec_child(path, input, sh);
// 	exec_parent(pid, sh);
// 	free(path);
// }
