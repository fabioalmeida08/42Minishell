/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:23:50 by marvin            #+#    #+#             */
/*   Updated: 2026/01/22 15:24:01 by fabialme         ###   ########.fr       */
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

static void	print_redir_info(t_redirect *redir, int depth)
{
	int	i;

	i = 0;
	while (i++ < depth + 1)
		printf("  ");
	if (redir->type == REDIR_HEREDOC)
		printf("REDIR %s %s (expand:%d)\n", redir_type_str(redir->type),
			redir->target, redir->expand);
	else
		printf("REDIR %s %s\n", redir_type_str(redir->type),
			redir->target);
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
		print_redir_info(redir, depth);
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
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
