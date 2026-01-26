/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:50:19 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/06 15:21:40 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print(char **cmd, int i, bool nl)
{
	while (cmd[i])
	{
		if (!cmd[i + 1])
			printf("%s", cmd[i]);
		else
			printf("%s ", cmd[i]);
		i++;
	}
	if (nl)
		printf("\n");
}

void	builtin_echo(char **cmd, t_shell *sh)
{
	if (cmd[1])
	{
		if (ft_strcmp(cmd[1], "-n") && cmd[2])
		{
			print(cmd, 2, false);
			sh->exit_status = 0;
		}
		else
		{
			print(cmd, 1, true);
			sh->exit_status = 0;
		}
	}
}
