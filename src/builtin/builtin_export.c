/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:07:49 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 16:07:49 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_print(t_shell *sh)
{
	t_env	*env_list;

	env_list = sh->env_list;
	while (env_list)
	{
		printf("declare -x %s", env_list->key);
		if (env_list->value)
			printf("=\"%s\"", env_list->value);
		printf("\n");
		env_list = env_list->next;
	}
}

static void	export_with_value(t_shell *sh, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (get_env_node(sh->env_list, key))
		update_env_var(sh->env_list, key, value);
	else
		add_env_var(&sh->env_list, key, value);
	free(key);
	free(value);
}

static void	export_without_value(t_shell *sh, char *key)
{
	if (get_env_node(sh->env_list, key))
		return ;
	add_env_var(&sh->env_list, key, NULL);
}

void	builtin_export(char **cmd, t_shell *sh)
{
	if (!cmd[1])
	{
		export_print(sh);
		return ;
	}
	if (ft_strchr(cmd[1], '='))
		export_with_value(sh, cmd[1]);
	else
		export_without_value(sh, cmd[1]);
}
