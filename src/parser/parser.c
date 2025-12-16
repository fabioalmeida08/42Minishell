/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:53:45 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/15 14:41:10 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_last_pipe(t_token *tokens)
{
	t_token	*last_pipe;
	t_token	*current;

	last_pipe = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TK_PIPE)
			last_pipe = current;
		current = current->next;
	}
	return (last_pipe);
}

t_ast	*parser_ast(t_token *tokens)
{
	t_token	*last_pipe;
	t_token	*right_tokens;
	t_token	*left_tokens;
	t_token	*prev;
	t_ast	*node;

	last_pipe = find_last_pipe(tokens);
	if (!last_pipe)
		return (parser_cmd(tokens));
	right_tokens = last_pipe->next;
	prev = tokens;
	while (prev && (prev->next != last_pipe))
		prev = prev->next;
	if (prev)
		prev->next = NULL;
	left_tokens = tokens;
	node = malloc(sizeof(t_ast));
	node->type = PIPE_NODE;
	node->left = parser_ast(left_tokens);
	node->right = parser_ast(right_tokens);
	return (node);
}
