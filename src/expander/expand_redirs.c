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

#include "../../includes/minishell.h"

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
	free_envp(expanded);
	return (res);
}

static bool	has_quotes(char *str)
{
	while(str && *str)
	{
		if (*str == '"' || *str == '\'')
			return (true);
		str++;
	}
	return (false);
}

static char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = 0;
	free(str);
	return (new_str);
}

void	normalize_heredoc(t_redirect *redirs)
{
	if(has_quotes(redirs->target))
	{
		redirs->expand = false;
		redirs->target = remove_quotes(redirs->target);
	}
	else
		redirs->expand = true;
}
