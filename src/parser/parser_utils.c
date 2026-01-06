/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:36:58 by marvin            #+#    #+#             */
/*   Updated: 2025/12/29 18:36:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(t_token *tok, t_shell *sh)
{
	ft_putstr_fd("syntax error near token ", 2);
	if (tok && tok->value)
		ft_putstr_fd(tok->value, 2);
	else if (tok)
	{
		if (tok->type == TK_PAREN_OPEN)
			ft_putstr_fd("(\n", 2);
		else if (tok->type == TK_PAREN_CLOSE)
			ft_putstr_fd(")\n", 2);
		else if (tok->type == TK_PIPE)
			ft_putstr_fd("|\n", 2);
		else if (tok->type == TK_REDIR_IN)
			ft_putstr_fd("<\n", 2);
		else if (tok->type == TK_REDIR_OUT)
			ft_putstr_fd(">\n", 2);
		else if (tok->type == TK_REDIR_APPEND)
			ft_putstr_fd(">>\n", 2);
		else if (tok->type == TK_REDIR_HEREDOC)
			ft_putstr_fd("<<\n", 2);
		else if (tok->type == TK_AND)
			ft_putstr_fd("&&\n", 2);
		else if (tok->type == TK_OR)
			ft_putstr_fd("||\n", 2);
	}
	sh->exit_status = 2;
}

t_ast	*create_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

void	paren_depth_checker(int *depth, t_token *current)
{
	if (current->type == TK_PAREN_OPEN)
		*depth += 1;
	else if (current->type == TK_PAREN_CLOSE)
		*depth -= 1;
}

void	free_cmd(t_redirect *redir, char **args)
{
	t_redirect	*tmp;
	int			i;

	if (args)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
	}
	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMD)
		free_cmd(node->redirs, node->args);
	free(node);
}
