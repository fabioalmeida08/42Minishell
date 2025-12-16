/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:04:53 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 16:11:22 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*node;

	node = get_env_node(env_list, key);
	if (node)
		return (node->value);
	else
		return (NULL);
}

int	update_env_var(t_env *env_list, char *key, char *value)
{
	t_env	*node;

	node = get_env_node(env_list, key);
	if (!node)
		return (0);
	free(node->value);
	node->value = ft_strdup(value);
	return (node->value != NULL);
}

int	remove_env_var(t_env **env_list, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env_list;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, key))
		{
			if (prev)
				prev->next = temp->next;
			else
				*env_list = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = temp;
	}
}
