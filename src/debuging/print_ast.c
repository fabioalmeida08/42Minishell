/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:23:50 by marvin            #+#    #+#             */
/*   Updated: 2025/12/29 17:23:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*redir_type_str(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return ("?");
}

static void	print_cmd(t_ast *node, int depth)
{
	int			i;
	t_redirect	*redir;

	printf("NODE_CMD");
	if (node->args && node->args[0])
	{
		printf(" | args: ");
		i = -1;
		while (node->args[++i])
			printf("%s ", node->args[i]);
	}
	printf("\n");
	redir = node->redirs;
	while (redir)
	{
		i = 0;
		while (i++ < depth + 1)
			printf("  ");
		printf("REDIR %s %s\n",
			redir_type_str(redir->type),
			redir->target);
		redir = redir->next;
	}
}

void	print_ast(t_ast *node, int depth)
{
	int			i;

	if (!node)
		return ;
	i = 0;
	while (i++ < depth)
		printf("  ");
	if (node->type == NODE_CMD)
		print_cmd(node, depth);
	else if (node->type == NODE_PIPE)
		printf("NODE_PIPE\n");
	else if (node->type == NODE_AND)
		printf("NODE_AND\n");
	else if (node->type == NODE_OR)
		printf("NODE_OR\n");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
