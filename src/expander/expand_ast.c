/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:18:58 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/08 16:42:20 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expand_str(char *str, t_shell *sh)
{
	int		i;

	(void) sh;
	i = 0;
	if (str && str[0] == '\'')
		return (NULL);
	if (str && str[0] == '$')
		return (get_env_value(sh->env_list, &str[1]));
	return (NULL);
}

static void	expand_args(char **args, t_shell *sh)
{
	int		i;
	char	*exp_str;

	i = 0;
	while (args[i])
	{
		exp_str = expand_str(args[i], sh);
		if (exp_str)
			args[i] = exp_str;
		i++;
	}
}

static void	expand_redir(t_redirect *redirs, t_shell *sh)
{
	char	*exp_str;

	if (!redirs)
		return ;
	while (redirs)
	{
		exp_str = expand_str(redirs->target, sh);
		if (exp_str)
			redirs->target = exp_str;
		redirs = redirs->next;
	}
}

void	expand_ast(t_ast *node, t_shell *sh)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		expand_args(node->args, sh);
		expand_redir(node->redirs, sh);
	}	
	expand_ast(node->left, sh);
	expand_ast(node->right, sh);
}
