/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:14 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/29 18:36:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*find_matching_paren(t_token *start, t_token *end)
{
	int		depth;
	t_token	*current_tk;

	depth = 1;
	current_tk = start;
	while (current_tk && current_tk != end)
	{
		paren_depth_checker(&depth, current_tk);
		if (depth == 0)
			return (current_tk);
		current_tk = current_tk->next;
	}
	return (NULL);
}

t_ast	*parser_cmd(t_token *start, t_token *end, t_shell *sh)
{
	t_ast	*new_node;
	t_token	*close_paren;

	if (!start || start == end)
		return (NULL);
	if (start->type == TK_PAREN_OPEN)
	{
		close_paren = find_matching_paren(start->next, end);
		if (!close_paren)
		{
			syntax_error(start, sh);
			return (NULL);
		}
		if (start->next == close_paren)
		{
			syntax_error(start, sh);
			return (NULL);
		}
		new_node = parser_logical(start->next, close_paren, sh);
	}
	else
		new_node = simple_cmd(start, end, sh);
	if (!new_node)
		return (NULL);
	return (new_node);
}
