/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:32 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/26 16:55:55 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	if (!value)
	{
		result = ft_strdup(tmp);
		free(tmp);
		return (result);
	}
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		count;
	int		i;

	count = env_size(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = join_key_value(env->key, env->value);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	update_shlvl(t_shell *shell_vars)
{
	int		lvl;
	char	*value;
	char	*new_value;

	value = get_env_value(shell_vars->env_list, "SHLVL");
	if (!value)
		lvl = 0;
	else
		lvl = ft_atoi(value);
	lvl++;
	new_value = ft_itoa(lvl);
	update_env_var(shell_vars->env_list, "SHLVL", new_value);
	free(new_value);
}
