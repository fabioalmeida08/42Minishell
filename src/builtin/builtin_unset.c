/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:07:42 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 16:07:42 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_unset(char **cmd, t_shell *sh)
{
	if (get_env_node(sh->env_list, cmd[1]))
		remove_env_var(&sh->env_list, cmd[1]);
}
