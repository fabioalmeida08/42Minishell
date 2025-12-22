/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:14 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/22 18:57:48 by bolegari         ###   ########.fr       */
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
	node->type = NODE_CMD;
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
	t_ast	*new_node;
	t_token	*sub_tokens;
	int		depth;

	if (!tokens)
		return (NULL);
	if (tokens->type == TK_PAREN_OPEN)
	{
		depth = 1;
		sub_tokens = complex_cmd(tokens->next, &depth);
		if (!sub_tokens)
			return (NULL);
		new_node = parser_logical(sub_tokens);
	}
	else
		new_node = simple_cmd(tokens);
	return (new_node);
}

t_token	*complex_cmd(t_token *tokens, int *depth)
{
	t_token	*end_sb;

	end_sb = tokens;
	while (end_sb)
	{
		paren_depth_counter(depth, end_sb);
		if (*depth == 0)
			break ;
		end_sb = end_sb->next;
	}
	if (!end_sb || *depth != 0)
		return (NULL);
	end_sb->next = NULL;
	return (tokens);
}

t_ast	*simple_cmd(t_token *tokens)
{
	int		argc;
	t_ast	*new_node;

	argc = count_args(tokens);
	new_node = init_cmd_node();
	if (!new_node)
		return (NULL);
	new_node->args = malloc(sizeof(char *) * (argc + 1));
	if (!new_node->args)
		return (NULL);
	fill_cmd_node(new_node, tokens);
	return (new_node);
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
	if (node->type == NODE_CMD)
	{
		printf("NODE_CMD: ");
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
	else if (node->type == NODE_PIPE)
		printf("NODE_PIPE\n");
	else if (node->type == NODE_AND)
		printf("NODE_AND\n");
	else if (node->type == NODE_OR)
		printf("NODE_OR\n");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}
