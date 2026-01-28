/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:18:58 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/20 15:24:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static bool	expand_redir(t_redirect *redirs, t_shell *sh)
{
	bool	error;
	char	*new;

	while (redirs)
	{
		if (redirs->type != REDIR_HEREDOC)
		{
			new = expand_redir_target(redirs->target, sh, &error);
			if (error)
			{
				sh->exit_status = 1;
				ft_putstr_fd(redirs->target, 2);
				ft_putendl_fd(": ambiguous redirect", 2);
				return (false);
			}
			free(redirs->target);
			redirs->target = new;
		}
		else
			normalize_heredoc(redirs);
		redirs = redirs->next;
	}
	return (true);
}

bool	expand_ast(t_ast *node, t_shell *sh)
{
	if (!node)
		return (true);
	if (node->type == NODE_CMD)
	{
		node->args = expand_args(node->args, sh);
		if (!expand_redir(node->redirs, sh))
			return (false);
	}
	if (!expand_ast(node->left, sh))
		return (false);
	if (!expand_ast(node->right, sh))
		return (false);
	return (true);
}
