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
	char	**expanded;
	char	*res;

	*error = false;
	expanded = ft_calloc(1, sizeof(char *));
	expanded[0] = NULL;
	expand_and_remove_quotes(target, sh, &expanded);
	if (!expanded || !expanded[0] || expanded[1])
	{
		*error = true;
		free_envp(expanded);
		return (NULL);
	}
	res = ft_strdup(expanded[0]);
	return (res);
}
