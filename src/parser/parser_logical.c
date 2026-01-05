/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:53:45 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/29 18:58:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_last_logical_node(t_token *start, t_token *end)
{
	int		depth;
	t_token	*current_tk;
	t_token	*last_logical;

	depth = 0;
	current_tk = start;
	last_logical = NULL;
	while (current_tk && current_tk != end)
	{
		paren_depth_checker(&depth, current_tk);
		if (current_tk->type == TK_AND || current_tk->type == TK_OR)
		{
			if (depth == 0)
				last_logical = current_tk;
		}
		current_tk = current_tk->next;
	}
	return (last_logical);
}

static t_ast	*create_one_node(t_token *last_logical)
{
	t_ast	*node;

	if (last_logical->type == TK_AND)
		node = create_node(NODE_AND);
	else
		node = create_node(NODE_OR);
	return (node);
}

t_ast	*parser_logical(t_token *start, t_token *end, t_shell *sh)
{
	t_token	*last_log;
	t_ast	*node;

	if (!start || start == end)
		return (NULL);
	last_log = find_last_logical_node(start, end);
	if (!last_log)
		return (parser_pipe(start, end, sh));
	if (!last_log->next || last_log == start || last_log->next == end)
	{
		syntax_error(last_log, sh);
		return (NULL);
	}
	node = create_one_node(last_log);
	if (!node)
		return (NULL);
	node->left = parser_logical(start, last_log, sh);
	node->right = parser_logical(last_log->next, end, sh);
	if (!node->left || !node->right)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}
