/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:27:23 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/26 18:29:29 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cmd_path(char *cmd, t_shell *sh)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (find_path(cmd, sh));
}

static void	handle_cmd_not_found(char *cmd, t_shell *sh)
{
	if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free_all_structs(sh);
	exit(127);
}

static void	run_child_process(t_ast *ast, t_shell *sh)
{
	char	*path;

	if (check_redirections(ast, sh) == -1)
	{
		free_all_structs(sh);
		exit(1);
	}
	if (!ast->args || !ast->args[0] )
	{
		free_all_structs(sh);
		exit(0);
	}
	path = get_cmd_path(ast->args[0], sh);
	if (!path)
		handle_cmd_not_found(ast->args[0], sh);
	execve(path, ast->args, env_to_envp(sh->env_list));
	perror("execve failed");
	free(path);
	free_all_structs(sh);
	exit(126);
}

static void	update_exit_status(t_shell *sh, int status)
{
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sh->exit_status = 128 + WTERMSIG(status);
		if (sh->exit_status == 130)
			write(1, "\n", 1);
		else if (sh->exit_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	execve_cmd(t_ast *ast, t_shell *sh)
{
	pid_t	pid;
	int		status;

	setup_execution_signals();
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		setup_interactive_parent_signals();
		return ;
	}
	if (pid == 0)
	{
		setup_child_signals();
		run_child_process(ast, sh);
	}
	waitpid(pid, &status, 0);
	update_exit_status(sh, status);
	setup_interactive_parent_signals();
}
