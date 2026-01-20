/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:32 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/06 12:10:36 by bolegari         ###   ########.fr       */
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
	int		updated_shlvl;
	char	*shlvl_char;

	updated_shlvl = ft_atoi(get_env_value(shell_vars->env_list, "SHLVL")) + 1;
	shlvl_char = ft_itoa(updated_shlvl);
	update_env_var(shell_vars->env_list, "SHLVL", shlvl_char);
	free(shlvl_char);
}
