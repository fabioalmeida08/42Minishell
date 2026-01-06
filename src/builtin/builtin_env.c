/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:08:57 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/10 16:08:57 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(char **cmd, t_shell *sh)
{
	int		i;
	char	**envp_recreated;

	(void)cmd;
	envp_recreated = env_to_envp(sh->env_list);
	i = 0;
	while (envp_recreated[i])
	{
		printf("%s\n", envp_recreated[i]);
		i++;
	}
	free_envp(envp_recreated);
}
