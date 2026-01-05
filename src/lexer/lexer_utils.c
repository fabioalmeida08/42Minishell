/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:32 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/05 16:39:21 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_syntax_error(t_token *token, t_shell *sh)
{
	if (token)
		ft_free_tokens(token);
	ft_putstr_fd("Syntax error\n", 2);
	sh->exit_status = 2;
}

static bool	check_quotes(const char *str)
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

t_token	*ft_tokenize(t_shell *sh)
{
	t_token	*tokens;

	tokens = NULL;
	if (!check_quotes(sh->input))
	{
		lexer_syntax_error(tokens, sh);
		return (NULL);
	}
	tokens = ft_strtok(sh->input, sh);
	if (tokens)
		print_tokens(tokens);
	if (!tokens)
		return (NULL);
	printf("LEXER SYNTAX OK !!!\n");
	return (tokens);
}
