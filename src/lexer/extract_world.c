/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:09:26 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/15 15:10:25 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_invalid_input(const char **str)
{
	if (!str || !*str || **str == 0)
		return (1);
	return (0);
}

static int	is_word_delimiter(char c)
{
	if (ft_is_whitespace(c) || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static int	handle_quotes(const char *s, size_t *len, char *quote)
{
	char	c;

	c = s[*len];
	if (*quote == 0 && (c == '\'' || c == '"'))
	{
		*quote = c;
		(*len)++;
		return (1);
	}
	if (*quote && c == *quote)
	{
		*quote = 0;
		(*len)++;
		return (1);
	}
	if (*quote == '"' && c == '\\')
	{
		(*len)++;
		if (s[*len])
			(*len)++;
		return (1);
	}
	return (0);
}

static size_t	get_word_len(const char *s)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (s[len])
	{
		if (handle_quotes(s, &len, &quote))
			continue ;
		if (quote == 0 && is_word_delimiter(s[len]))
			break ;
		len++;
	}
	return (len);
}

char	*extract_word(const char **str)
{
	char	*word;
	size_t	len;

	if (is_invalid_input(str))
		return (NULL);
	len = get_word_len(*str);
	if (len == 0)
		return (NULL);
	word = ft_strndup(*str, len);
	*str += len;
	return (word);
}
