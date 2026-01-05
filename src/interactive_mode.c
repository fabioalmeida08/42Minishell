/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/05 16:45:49 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_ast *ast, t_shell *sh)
{
	if (is_builtin(ast->args, sh))
		exec_builtin(ast->args, sh);
	else
		execve_cmd(ast->args, sh);
}

void	execute_ast(t_ast *ast, t_shell *sh)
{
	if (ast->type == NODE_CMD)
		execute_cmd(ast, sh);
	if (ast->type == NODE_PIPE)
		execute_pipe(ast, sh);
}

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

void	interactive_mode(t_shell *sh)
{
	while (1)
	{
		sh->input = readline("Minishell> ");
		if (sh->input == NULL)
			break ;
		add_history(sh->input);
		sh->head_tokens = ft_tokenize(sh);
		sh->head_ast = parser_logical(sh->head_tokens, NULL, sh);
		if (!sh->head_ast)
		{
			free(sh->input);
			continue ;
		}
		print_ast(sh->head_ast, 1);
		execute_ast(sh->head_ast, sh);
		free_internal_use_structs(sh);
		free(sh->input);
	}
	rl_clear_history();
	free_all_structs(sh);
}
