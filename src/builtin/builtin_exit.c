/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:40:07 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/27 16:48:25 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_numeric (char *ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		if (!ft_isdigit(ptr[i++]))
			return false;
	return true;
}

static bool	check_numeric(char **cmd, int i)
{
	while (cmd[i])
	{
		if (!is_numeric(cmd[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": numeric arguments required\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_number_args(char **cmd, int i)
{
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (false);
	}
	return (true);

}

void	builtin_exit(char **cmd, t_shell *sh)
{
	int i;

	i = 1;
	if (!cmd[i])
	{
		sh->running = false;
		return ;
	}
	if (!check_numeric(cmd, i))
		return ;
	if (!check_number_args(cmd, 1))
		return ;
	i = 1;
	sh->exit_status = ft_atoi(cmd[i]);
	sh->running = false;
}
