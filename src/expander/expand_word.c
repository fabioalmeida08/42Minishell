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
	char	**args;

	args = ft_calloc(1, sizeof(char *));
	args[0] = NULL;
	expand_and_remove_quotes(str, sh, &args);
	return (args);
}
