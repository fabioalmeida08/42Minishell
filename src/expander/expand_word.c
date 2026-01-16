/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:49:28 by marvin            #+#    #+#             */
/*   Updated: 2026/01/12 15:49:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**expand_word(char *str, t_shell *sh)
{
	char	**res;
	char	*expanded;
	bool	can_split;

	can_split = false;
	expanded = expand_and_remove_quotes(str, sh, &can_split);
	if (can_split)
	{
		res = ft_split(expanded, ' ');
		free(expanded);
	}
	else
	{
		res = ft_calloc(2, sizeof(char *));
		res[0] = expanded;
		res[1] = NULL;
	}
	return (res);
}
