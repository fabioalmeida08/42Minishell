/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:53:45 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/22 17:49:49 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_last_node(t_token *tokens, t_token_type to_find)
{
	t_token	*last_pipe;
	t_token	*current;
	int		depth;

	depth = 0;
	last_pipe = NULL;
	current = tokens;
	while (current)
	{
		paren_depth_counter(&depth, current);
		if (current->type == to_find && depth == 0)
			last_pipe = current;
		current = current->next;
	}
	return (last_pipe);
}

t_ast	*parser_pipe(t_token *tokens)
{
	t_token	*last_pipe;
	t_token	*right_tokens;
	t_token	*left_tokens;
	t_ast	*node;

	last_pipe = find_last_node(tokens, TK_PIPE);
	if (!last_pipe)
		return (parser_cmd(tokens));
	right_tokens = last_pipe->next;
	brake_list_until(tokens, last_pipe);
	left_tokens = tokens;
	node = create_node(NODE_PIPE);
	node->left = parser_pipe(left_tokens);
	node->right = parser_pipe(right_tokens);
	return (node);
}
