/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:12:56 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/02 09:33:38 by marvin           ###   ########.fr       */
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

static t_token_type	get_double_operator_type(const char *s, size_t *len)
{
	*len = 2;
	if (is_double_operator(s, '|'))
		return (TK_OR);
	if (is_double_operator(s, '&'))
		return (TK_AND);
	if (is_double_operator(s, '<'))
		return (TK_REDIR_HEREDOC);
	if (is_double_operator(s, '>'))
		return (TK_REDIR_APPEND);
	return (TK_UNKNOWN);
}

static t_token_type	get_single_operator_type(const char *s, size_t *len)
{
	*len = 1;
	if (s[0] == '|')
		return (TK_PIPE);
	if (s[0] == '<')
		return (TK_REDIR_IN);
	if (s[0] == '>')
		return (TK_REDIR_OUT);
	if (s[0] == '(')
		return (TK_PAREN_OPEN);
	if (s[0] == ')')
		return (TK_PAREN_CLOSE);
	return (TK_UNKNOWN);
}

t_token	*handle_operator(const char **str)
{
	t_token_type	type;
	size_t			len;
	char			*value;
	t_token			*res;

	if (is_invalid_operator_input(str))
		return (NULL);
	type = get_double_operator_type(*str, &len);
	if (type == TK_UNKNOWN)
	{
		type = get_single_operator_type(*str, &len);
		if (type == TK_UNKNOWN)
			return (NULL);
	}
	value = NULL;
	*str += len;
	res = create_token(type, value);
	return (res);
}
