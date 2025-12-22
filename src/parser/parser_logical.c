/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:53:45 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/22 17:49:17 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

void	brake_list_until(t_token *list, t_token *until)
{
	t_token	*prev;

	prev = list;
	while (prev && (prev->next != until))
		prev = prev->next;
	if (prev)
		prev->next = NULL;
}

void	paren_depth_counter(int *depth, t_token *current)
{
	if (current->type == TK_PAREN_OPEN)
		*depth += 1;
	else if (current->type == TK_PAREN_CLOSE)
		*depth -= 1;
}

t_token	*find_last_logical_node(t_token *tokens)
{
	t_token	*last_logical;
	t_token	*current;
	int		depth;

	depth = 0;
	last_logical = NULL;
	current = tokens;
	while (current)
	{
		paren_depth_counter(&depth, current);
		if ((current->type == TK_AND || current->type == TK_OR) && depth == 0)
			last_logical = current;
		current = current->next;
	}
	return (last_logical);
}

t_ast	*parser_logical(t_token *tokens)
{
	t_token	*last_logical;
	t_token	*right_tokens;
	t_token	*left_tokens;
	t_ast	*node;

	last_logical = find_last_logical_node(tokens);
	if (!last_logical)
		return (parser_pipe(tokens));
	right_tokens = last_logical->next;
	brake_list_until(tokens, last_logical);
	left_tokens = tokens;
	if (last_logical->type == TK_AND)
		node = create_node(NODE_AND);
	else
		node = create_node(NODE_OR);
	node->left = parser_logical(left_tokens);
	node->right = parser_logical(right_tokens);
	return (node);
}
