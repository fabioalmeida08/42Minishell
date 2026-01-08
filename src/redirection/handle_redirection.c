/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:21:28 by marvin            #+#    #+#             */
/*   Updated: 2025/12/29 17:21:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redir(t_token_type type)
{
	return (
		type == TK_REDIR_IN
		|| type == TK_REDIR_OUT
		|| type == TK_REDIR_APPEND
		|| type == TK_REDIR_HEREDOC
	);
}

static t_redir_type	token_to_redir(t_token_type type)
{
	if (type == TK_REDIR_IN)
		return (REDIR_IN);
	if (type == TK_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TK_REDIR_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

void	add_redir(t_ast *node, t_redirect *new_redir)
{
	t_redirect	*tmp;

	if (!node->redirs)
	{
		node->redirs = new_redir;
		return ;
	}
	tmp = node->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

void	handle_redirection(t_ast *node, t_token *redir, t_token *target)
{
	t_redirect	*redir_node;

	redir_node = malloc(sizeof(t_redirect));
	if (!redir_node)
		return ;
	redir_node->type = token_to_redir(redir->type);
	redir_node->target = ft_strdup(target->value);
	redir_node->next = NULL;
	redir_node->fd = -1;
	add_redir(node, redir_node);
}
