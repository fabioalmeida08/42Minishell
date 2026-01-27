/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:07:49 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/27 16:10:12 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_export(t_shell *sh, char *arg)
{
	char	*eq;
	char	*key;
	char	*val;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		val = ft_strdup(eq + 1);
		if (get_env_node(sh->env_list, key))
			update_env_var(sh->env_list, key, val);
		else
			add_env_var(&sh->env_list, key, val);
		free(key);
		free(val);
	}
	else if (!get_env_node(sh->env_list, arg))
		add_env_var(&sh->env_list, arg, NULL);
}

static void	print_export_error(char *arg, t_shell *sh)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	sh->exit_status = 1;
}

void	builtin_export(char **cmd, t_shell *sh)
{
	int	i;

	sh->exit_status = 0;
	if (!cmd[1])
	{
		export_print(sh);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
			print_export_error(cmd[i], sh);
		else
			handle_export(sh, cmd[i]);
		i++;
	}
}
