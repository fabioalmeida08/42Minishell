/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/29 17:54:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_ast *ast, t_shell *sh)
{
	// Se for builtin, usa a lógica de Salvar/Restaurar
	if (is_builtin(ast->args, sh))
		execute_builtin_with_redir(ast, sh);
	else
		// Se for externo, passa o AST inteiro para lidar com o fork
        // Lembre-se de atualizar o protótipo de execve_cmd no header!
		execve_cmd(ast, sh); 
}
// void	execute_cmd(t_ast *ast, t_shell *sh)
// {
// 	if (is_builtin(ast->args, sh))
// 		exec_builtin(ast->args, sh);
// 	else
// 		execve_cmd(ast->args, sh);
// }

void	execute_ast(t_ast *ast, t_shell *sh)
{
	if (ast->type == NODE_CMD)
		execute_cmd(ast, sh);
	if (ast->type == NODE_PIPE)
		execute_pipe(ast, sh);
}

void	free_internal_use_structs(t_shell *sh)
{
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
		sh->head_ast = parser_logical(sh->head_tokens, NULL, sh);
		if (!sh->head_tokens || !sh->head_ast)
		{
			free(input);
			continue ;
		}
		execute_ast(sh->head_ast, sh);
		free_internal_use_structs(sh);
		free(input);
		printf("LAST EXIT CODE = %d\n", sh->exit_status);
  }
  free_all_structs(sh);
}
