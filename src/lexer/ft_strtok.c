/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:17:56 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/02 09:34:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_whitespace(const char **str)
{
	while (**str && ft_is_whitespace(**str))
		(*str)++;
}

static int	process_operator(const char **str, t_token **tokens, t_shell *sh)
{
	t_token	*token;

	token = handle_operator(str);
	if (!token || token->type == TK_REDIR_HEREDOC)
	{
		if (token->type == TK_REDIR_HEREDOC)
			ft_putstr_fd("HEREDOC IS NOT IMPLEMENTED YET !!! \n", 2);
		else
			lexer_syntax_error(*tokens, sh);
		return (0);
	}
	add_token_back(tokens, token);
	return (1);
}

static int	process_word(const char **str, t_token **tokens, t_shell *sh)
{
	t_token	*token;
	char	*word;

	word = extract_word(str);
	if (!word)
		return (1);
	token = create_token(TK_WORD, word);
	if (!token)
	{
		free(word);
		lexer_syntax_error(*tokens, sh);
		return (0);
	}
	add_token_back(tokens, token);
	return (1);
}

t_token	*ft_strtok(const char *str, t_shell *sh)
{
	t_token	*tokens;

	tokens = NULL;
	while (*str)
	{
		skip_whitespace(&str);
		if (*str == '\0')
			break ;
		if (*str == '|' || *str == '<' || *str == '>' || *str == '&'
			|| *str == '(' || *str == ')')
		{
			if (!process_operator(&str, &tokens, sh))
				return (NULL);
		}
		else if (!process_word(&str, &tokens, sh))
			return (NULL);
	}
	return (tokens);
}
