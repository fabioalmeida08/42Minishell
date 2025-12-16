/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:12:56 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/16 16:21:54 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_invalid_operator_input(const char **str)
{
	if (!str || !*str || **str == '\0')
		return (1);
	return (0);
}

static int	is_double_operator(const char *s, char op)
{
	return (s[0] == op && s[1] == op);
}

static t_token_type	get_operator_type(const char *s, size_t *len)
{
	*len = 1;
	if (s[0] == '|')
		return (TK_PIPE);
	if (is_double_operator(s, '<'))
	{
		*len = 2;
		return (TK_REDIR_HEREDOC);
	}
	if (is_double_operator(s, '>'))
	{
		*len = 2;
		return (TK_REDIR_APPEND);
	}
	if (s[0] == '<')
		return (TK_REDIR_IN);
	return (TK_REDIR_OUT);
}

t_token	*handle_operator(const char **str)
{
	t_token_type	type;
	size_t			len;
	char			*value;
	t_token			*res;

	if (is_invalid_operator_input(str))
		return (NULL);
	type = get_operator_type(*str, &len);
	value = ft_strndup(*str, len);
	if (!value)
		return (NULL);
	*str += len;
	res = create_token(type, value);
	return (res);
}
