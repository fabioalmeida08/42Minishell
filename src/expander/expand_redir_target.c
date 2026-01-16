/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir_target.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:50:56 by marvin            #+#    #+#             */
/*   Updated: 2026/01/12 17:50:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_redir_target(char *target, t_shell *sh, bool *error)
{
	char	*expanded;
	bool	can_split;
	char	**split;

	*error = false;
	can_split = false;
	expanded = expand_and_remove_quotes(target, sh, &can_split);
	if (!can_split)
		return (expanded);
	split = ft_split(expanded, ' ');
	free(expanded);
	if (!split || !split[0] || split[1])
	{
		*error = true;
		free_envp(split);
		return (NULL);
	}
	expanded = ft_strdup(split[0]);
	free_envp(split);
	return (expanded);
}
