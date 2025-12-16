/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:32 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/15 15:22:45 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*lexer_syntax_error(t_token *token, t_shell *sh)
{
	if (token)
	{
		free(token->value);
		free(token);
	}
	ft_putstr_fd("Syntax error\n", 2);
	sh->exit_status = 2;
	return (NULL);
}

bool	check_syntax(const char *str)
{
	bool	in_single;
	bool	in_double;
	bool	escaped;

	in_single = false;
	in_double = false;
	escaped = false;
	while (*str)
	{
		if (escaped)
			escaped = false;
		if (*str == '\\' && !in_single)
			escaped = true;
		else if (*str == '\'' && !in_double)
			in_single = !in_single;
		else if (*str == '\"' && !in_single)
			in_double = !in_double;
		str++;
	}
	return (!in_single && !in_double && !escaped);
}

t_token	*ft_tokenize(const char *str, t_shell *sh)
{
	t_token	*tokens;

	tokens = NULL;
	if (!check_syntax(str))
		return (lexer_syntax_error(tokens, sh));
	tokens = ft_strtok(str, sh);
	if (!tokens)
		return (NULL);
	print_tokens(tokens);
	return (tokens);
}
