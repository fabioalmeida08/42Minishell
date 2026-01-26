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

void print(char **cmd)
{
	int i;

	i = 1;

	while (cmd[i])
		printf("%s ",cmd[i++]);
	printf("\n");
}

{
void	builtin_echo(char **cmd, t_shell *sh)
	if (cmd[1])
	{
		if (ft_strcmp(cmd[1], "-n") && cmd[2])
		{
			printf("%s", cmd[2]);
			sh->exit_status = 0;
		}
		else
		{
			print(cmd);
			sh->exit_status = 0;
		}
	}
}
