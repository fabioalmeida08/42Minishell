/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/16 14:38:23 by bolegari         ###   ########.fr       */
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
	if (ast->type == CMD_NODE)
		execute_cmd(ast, sh);
	if (ast->type == PIPE_NODE)
		execute_pipe(ast, sh);
}


void	interactive_mode(t_shell *sh)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell> ");
		if (input == NULL)
		{
			free(input);
			break ;
		}
		add_history(input);
		sh->head_tokens = ft_tokenize(input, sh);
		if (!sh->head_tokens)
		{
			free(input);
			continue ;
		}
		sh->head_ast = parser_ast(sh->head_tokens);
		// print_ast(sh->head_ast, 1);
		execute_ast(sh->head_ast, sh);
		ft_free_tokens(sh->head_tokens);
		sh->head_tokens = NULL;
		free(input);
	}
	ft_free_tokens(sh->head_tokens);
	free(sh->g_builtins);
	free_env_list(sh->env_list);
}
