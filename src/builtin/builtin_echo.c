/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:50:19 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/06 15:00:34 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	builtin_echo(char **cmd, t_shell *sh)
{
	if (ft_strcmp(cmd[1], "-n") && cmd[2])
	{
		printf("%s",cmd[2]);
		sh->exit_status = 1;
	}
	else if (cmd[2])
	{
		printf("%s\n",cmd[2]);
		sh->exit_status = 1;
	}
}
