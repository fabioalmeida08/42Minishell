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

t_token	*find_last_node(t_token *start, t_token *end, t_token_type to_find)
{
	int		depth;
	t_token	*current_tk;
	t_token	*last_pipe;

	depth = 0;
	current_tk = start;
	last_pipe = NULL;
	while (current_tk && current_tk != end)
	{
		paren_depth_checker(&depth, current_tk);
		if (current_tk->type == to_find && depth == 0)
			last_pipe = current_tk;
		current_tk = current_tk->next;
	}
	return (last_pipe);
}

t_ast	*parser_pipe(t_token *start, t_token *end, t_shell *sh)
{
	t_token	*last_pipe;
	t_ast	*node;

	if (!start || start == end)
		return (NULL);
	last_pipe = find_last_node(start, end, TK_PIPE);
	if (!last_pipe)
		return (parser_cmd(start, end, sh));
	if (!last_pipe->next || last_pipe == start || last_pipe->next == end)
	{
		syntax_error(last_pipe, sh);
		return (NULL);
	}
	node = create_node(NODE_PIPE);
	if (!node)
		return (NULL);
	node->left = parser_pipe(start, last_pipe, sh);
	node->right = parser_pipe(last_pipe->next, end, sh);
	if (!node->left || !node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}
