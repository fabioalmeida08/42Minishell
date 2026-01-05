/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:13:12 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/18 17:31:11 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	key_value_breaker(char *envp, char **key, char **value)
{
	char	*eq;

	eq = strchr(envp, '=');
	if (eq)
	{
		*eq = 0;
		*key = ft_strdup(envp);
		*value = ft_strdup(eq + 1);
		*eq = '=';
	}
	else
	{
		*key = ft_strdup(envp);
		*value = NULL;
	}
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	if (!new_node->key || (value && !new_node->value))
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static int	append_env_list(t_env **head, t_env *new_node)
{
	t_env	*temp;

	if (!new_node)
		return (0);
	if (*head == NULL)
	{
		*head = new_node;
		return (1);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return (1);
}

int	add_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return (0);
	return (append_env_list(env_list, new_node));
}

void	init_env(char **envp, t_shell *shell_vars)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*node;

	i = 0;
	shell_vars->envp = envp;
	shell_vars->env_list = NULL;
	shell_vars->head_tokens = NULL;
	shell_vars->exit_status = 0;
	while (envp[i])
	{
		key_value_breaker(envp[i], &key, &value);
		node = create_env_node(key, value);
		free(key);
		free(value);
		if (!append_env_list(&shell_vars->env_list, node))
		{
			free_env_list(shell_vars->env_list);
			return ;
		}
		i++;
	}
	i = ft_atoi(get_env_value(shell_vars->env_list, "SHLVL")) + 1;
	update_env_var(shell_vars->env_list, "SHLVL", ft_itoa(i));
}
