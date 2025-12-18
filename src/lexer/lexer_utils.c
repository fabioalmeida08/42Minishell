/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:32 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/18 14:21:25 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	checker(t_token *token, int *paren_balance, bool *res)
{
	if (token->type == TK_PAREN_OPEN)
	{
		*paren_balance += 1;
		if (!token->next || token->next->type == TK_PAREN_CLOSE)
			res = false;
	}
	else if (token->type == TK_PAREN_CLOSE)
	{
		*paren_balance -= 1;
		if (*paren_balance < 0)
			res = false;
	}
	else if (token->type != TK_WORD)
	{
		if (!token->next || token->next->type != TK_WORD)
			res = false;
	}
}

void	lexer_syntax_error(t_token *token, t_shell *sh)
{
	if (token)
		ft_free_tokens(token);
	ft_putstr_fd("Syntax error\n", 2);
	sh->exit_status = 2;
}

bool	check_quotes(const char *str)
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

bool	check_token_syntax(t_token *token, t_shell *sh)
{
	bool	res;
	int		paren_balance;

	res = false;
	paren_balance = 0;
	if (token->type == TK_WORD || token->type == TK_PAREN_OPEN)
		res = true;
	while (token)
	{
		checker(token, &paren_balance, &res);
		if (!res)
		{
			lexer_syntax_error(token, sh);
			break ;
		}
		token = token->next;
	}
	if (paren_balance != 0 && res)
	{
		res = false;
		lexer_syntax_error(token, sh);
	}
	return (res);
}

t_token	*ft_tokenize(const char *str, t_shell *sh)
{
	t_token	*tokens;

	tokens = NULL;
	if (!check_quotes(str))
	{
		lexer_syntax_error(tokens, sh);
		return (NULL);
	}
	tokens = ft_strtok(str, sh);
	print_tokens(tokens);
	if (!tokens || !check_token_syntax(tokens, sh))
		return (NULL);
	printf("SYNTAX OK !!!\n");
	return (tokens);
}
