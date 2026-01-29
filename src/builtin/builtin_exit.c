/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:40:07 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/29 14:12:03 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_with_error(t_shell *sh, char *arg, char *msg, int status)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	free_all_structs(sh);
	exit(status);
}

void	builtin_exit(char **cmd, t_shell *sh)
{
	long long	exit_val;

	if (sh->interactive)
		ft_putendl_fd("exit", 1);
	if (!cmd[1])
	{
		exit_val = sh->exit_status;
		free_all_structs(sh);
		exit(exit_val);
	}
	if (!ft_atoll_checked(cmd[1], &exit_val))
		exit_with_error(sh, cmd[1], "numeric argument required", 2);
	if (cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		sh->exit_status = 1;
		return ;
	}
	free_all_structs(sh);
	exit((unsigned char)exit_val);
}
