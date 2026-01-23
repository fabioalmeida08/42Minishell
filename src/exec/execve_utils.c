/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:08:54 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/16 16:09:09 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = try_path(paths[i], cmd);
		if (full_path)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_shell *sh)
{
	char	**paths;
	char	*path_value;
	char	*result;

	path_value = get_env_value(sh->env_list, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_envp(paths);
	return (result);
}

void	exec_child(char *path, char **input, t_shell *sh)
{
	char	**envp;

	envp = env_to_envp(sh->env_list);
	execve(path, input, envp);
	perror("execve");
	free_envp(envp);
	exit(1);
}

void	exec_parent(pid_t pid, t_shell *sh)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else
		sh->exit_status = 1;
}
