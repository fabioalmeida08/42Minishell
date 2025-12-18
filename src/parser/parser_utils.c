/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:14 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/18 14:32:49 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TK_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static t_ast	*init_cmd_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = CMD_NODE;
	node->left = NULL;
	node->right = NULL;
	node->in = NULL;
	node->out = NULL;
	node->args = NULL;
	return (node);
}

static void	handle_redirection(t_ast *node, t_token **current)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return ;
	redir->type = (*current)->type;
	redir->content = NULL;
	if ((*current)->next)
		redir->file = ft_strdup((*current)->next->value);
	if (redir->type == TK_REDIR_IN || redir->type == TK_REDIR_HEREDOC)
		node->in = redir;
	else
		node->out = redir;
	*current = (*current)->next;
}

static void	fill_cmd_node(t_ast *node, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == TK_WORD)
			node->args[i++] = ft_strdup(tokens->value);
		else if (tokens->type == TK_REDIR_IN
			|| tokens->type == TK_REDIR_OUT
			|| tokens->type == TK_REDIR_APPEND
			|| tokens->type == TK_REDIR_HEREDOC)
			handle_redirection(node, &tokens);
		tokens = tokens->next;
	}
	node->args[i] = NULL;
}

t_ast	*parser_cmd(t_token *tokens)
{
	t_ast	*node;
	int		argc;

	if (!tokens)
		return (NULL);
	node = init_cmd_node();
	if (!node)
		return (NULL);
	argc = count_args(tokens);
	node->args = malloc(sizeof(char *) * (argc + 1));
	if (!node->args)
		return (NULL);
	fill_cmd_node(node, tokens);
	return (node);
}

//TODO: debug 
void	print_ast(t_ast *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (node->type == CMD_NODE)
	{
		printf("CMD_NODE: ");
		i = 0;
		while (node->args[i])
		{
			printf("%s ", node->args[i]);
			i++;
		}
		printf("\n");
		if (node->in)
			printf("%*sIN REDIR: %s\n", depth * 2 + 2, "", node->in->file);
		if (node->out)
			printf("%*sOUT REDIR: %s\n", depth * 2 + 2, "", node->out->file);
	}
	else if (node->type == PIPE_NODE)
		printf("PIPE_NODE\n");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
