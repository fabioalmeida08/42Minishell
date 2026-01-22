/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/22 15:21:03 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_internal_use_structs(t_shell *sh)
{
	if (sh->input)
		free(sh->input);
	if (sh->head_ast)
	{
		free_ast(sh->head_ast);
		sh->head_ast = NULL;
	}
	if (sh->head_tokens)
	{
		ft_free_tokens(sh->head_tokens);
		sh->head_tokens = NULL;
	}
}

void	free_all_structs(t_shell *sh)
{
	free_internal_use_structs(sh);
	if (sh->g_builtins)
		free(sh->g_builtins);
	free_env_list(sh->env_list);
}

void	clear_and_free(t_shell *sh)
{
	rl_clear_history();
	free_all_structs(sh);
}

void	interactive_mode(t_shell *sh)
{
	while (sh->running)
	{
		sh->input = readline("Minishell> ");
		if (sh->input == NULL)
			break ;
		add_history(sh->input);
		sh->head_tokens = ft_tokenize(sh);
		sh->head_ast = parser_logical(sh->head_tokens, NULL, sh);
		if (!sh->head_ast)
		{
			free_internal_use_structs(sh);
			continue ;
		}
		expand_ast(sh->head_ast, sh);
		if (!sh->head_tokens || !sh->head_ast)
		{
			free_internal_use_structs(sh);
			continue ;
		}
		execute_ast(sh->head_ast, sh);
		if (sh->running)
			free_internal_use_structs(sh);
	}
	clear_and_free(sh);
}
