/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:08:48 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/27 16:09:02 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sort_env_array(t_env **arr, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_var(t_env *env)
{
	if (ft_strcmp(env->key, "_") != 0)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
	}
}

void	export_print(t_shell *sh)
{
	t_env	**arr;
	t_env	*tmp;
	int		len;
	int		i;

	len = 0;
	tmp = sh->env_list;
	while (tmp && ++len)
		tmp = tmp->next;
	arr = ft_calloc(len + 1, sizeof(t_env *));
	if (!arr)
		return ;
	tmp = sh->env_list;
	i = -1;
	while (tmp)
	{
		arr[++i] = tmp;
		tmp = tmp->next;
	}
	sort_env_array(arr, len);
	i = -1;
	while (++i < len)
		print_export_var(arr[i]);
	free(arr);
}
