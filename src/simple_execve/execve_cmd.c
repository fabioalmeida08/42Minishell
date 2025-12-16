/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:27:23 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 11:36:22 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*try_path(char *dir, char *cmd)
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

static char	*search_in_paths(char **paths, char *cmd)
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

static char	*find_path(char *cmd, t_shell *sh)
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
// static char	*find_path(char *cmd, t_shell *sh)
// {
// 	char	**paths;
// 	char	*path_value;
// 	char	*full_path;
// 	char	*tmp;
// 	int		i;
//
// 	path_value = get_env_value(sh->env_list, "PATH");
// 	if (!path_value)
// 		return (NULL);
// 	paths = ft_split(path_value, ':');
// 	if (!paths)
// 		return (NULL);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			free_envp(paths);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	free_envp(paths);
// 	return (NULL);
// }

void	execve_cmd(char **input, t_shell *sh)
{
	char	**envp_recreated;
	char	*full_path;
	pid_t	pid;
	int		status;

	full_path = find_path(input[0], sh);
	if (full_path && access(full_path, X_OK) == 0)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("FORK");
			return ;
		}
		else if (pid == 0)
		{
			envp_recreated = env_to_envp(sh->env_list);
			execve(full_path, input, envp_recreated);
			free_envp(envp_recreated);
			exit(1);
		}
		else
			waitpid(pid, &status, 0);
	}
	free(full_path);
}
