/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:39:39 by marvin            #+#    #+#             */
/*   Updated: 2025/12/29 18:39:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_token *start, t_token *end, t_token **err_token)
{
	int		count;

	count = 0;
	while (start && start != end)
	{
		if (start->type == TK_WORD)
			count++;
		else if (is_redir(start->type))
		{
			if (!start->next || start->next->type != TK_WORD)
			{
				*err_token = start;
				return (-1);
			}
			if (start->next->next && start->next->next->type == TK_WORD)
			{
				*err_token = start->next->next;
				return (-1);
			}
			start = start->next;
		}
		start = start->next;
	}
	return (count);
}

static t_ast	*init_cmd_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
}

static bool	fill_cmd(t_token *start, t_token *end, t_ast *node)
{
	int		i;

	i = 0;
	while (start && start != end)
	{
		if (start->type == TK_WORD)
		{
			node->args[i++] = ft_strdup(start->value);
			start = start->next;
		}
		else if (is_redir(start->type))
		{
			handle_redirection(node, start, start->next);
			start = start->next->next;
		}
	}
	node->args[i] = NULL;
	return (true);
}

t_ast	*simple_cmd(t_token *start, t_token *end, t_shell *sh)
{
	int		argc;
	t_ast	*new_node;
	t_token	*err_token;

	argc = count_args(start, end, &err_token);
	if (argc < 0)
	{
		syntax_error(err_token, sh);
		return (NULL);
	}
	new_node = init_cmd_node();
	if (!new_node)
		return (NULL);
	new_node->args = malloc(sizeof(char *) * (argc + 1));
	if (!new_node->args)
	{
		free(new_node);
		return (NULL);
	}
	if (!fill_cmd(start, end, new_node))
	{
		free_ast(new_node);
		return (NULL);
	}
	return (new_node);
}
