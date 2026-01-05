/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:09:12 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/05 16:53:26 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_builtins(t_builtin *b)
{
	b[0].name = "pwd";
	b[0].func = builtin_pwd;
	b[1].name = "env";
	b[1].func = builtin_env;
	b[2].name = "export";
	b[2].func = builtin_export;
	b[3].name = "unset";
	b[3].func = builtin_unset;
	b[4].name = "cd";
	b[4].func = builtin_cd;
	b[5].name = NULL;
	b[5].func = NULL;
}

void	init_builtin(t_shell *sh)
{
	t_builtin	builtins[6];
	int			n;

	fill_builtins(builtins);
	n = 0;
	while (builtins[n].name)
		n++;
	sh->g_builtins = malloc(sizeof(t_builtin) * (n + 1));
	if (!sh->g_builtins)
		perror("g_builtins MALLOC FAILED");
	n = 0;
	while (builtins[n].name)
	{
		sh->g_builtins[n] = builtins[n];
		n++;
	}
	sh->g_builtins[n].name = NULL;
	sh->g_builtins[n].func = NULL;
}

int	is_builtin(char **cmd, t_shell *sh)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (sh->g_builtins[i].name)
	{
		if (ft_strcmp(cmd[0], sh->g_builtins[i].name))
		{
			res = 1;
			break ;
		}
		i++;
	}
	return (res);
}

void	exec_builtin(char **cmd, t_shell *sh)
{
	int	i;

	i = 0;
	printf("BUILTIN !!! \n");
	while (sh->g_builtins[i].name)
	{
		if (ft_strcmp(cmd[0], sh->g_builtins[i].name))
		{
			sh->g_builtins[i].func(cmd, sh);
			break ;
		}
		i++;
	}
}
