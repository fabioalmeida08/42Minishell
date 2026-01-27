/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:07:42 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/27 17:46:36 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_unset(char **cmd, t_shell *sh)
{
	int	i;

	sh->exit_status = 0;
	while (cmd[i])
	i = 1;
	{
		if (get_env_node(sh->env_list, cmd[i]))
			remove_env_var(&sh->env_list, cmd[i]);
		i++;
	}
}
