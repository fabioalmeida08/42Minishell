/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:18:58 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/18 21:32:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	args_len(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

void	append_all(char ***dst, char **src)
{
	char	**new;
	int		len_dst;
	int		i;

	if (!src || !src[0])
		return ;
	len_dst = args_len(*dst);
	new = ft_calloc(len_dst + args_len(src) + 1, sizeof(char *));
	if (!new)
		return ;
	i = 0;
	while (i < len_dst)
	{
		new[i] = (*dst)[i];
		i++;
	}
	i = 0;
	while (src[i])
	{
		new[len_dst + i] = src[i];
		i++;
	}
	free(*dst);
	*dst = new;
}

static char	**expand_args(char **args, t_shell *sh)
{
	int		i;
	char	**expanded;
	char	**new_args;

	i = 0;
	new_args = ft_calloc(1, sizeof(char *));
	new_args[0] = NULL;
	while (args[i])
	{
		expanded = expand_word(args[i], sh);
		append_all(&new_args, expanded);
		free(expanded);
		i++;
	}
	free_envp(args);
	return (new_args);
}

static void	expand_redir(t_redirect *redirs, t_shell *sh)
{
	bool	error;
	char	*new;

	while (redirs)
	{
		new = expand_redir_target(redirs->target, sh, &error);
		if (error)
		{
			sh->exit_status = 1;
			ft_putendl_fd("Minishell> ambiguous redirect", 2);
			return ;
		}
		free(redirs->target);
		redirs->target = new;
		redirs = redirs->next;
	}
}

void	expand_ast(t_ast *node, t_shell *sh)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		node->args = expand_args(node->args, sh);
		expand_redir(node->redirs, sh);
	}
	expand_ast(node->left, sh);
	expand_ast(node->right, sh);
}
