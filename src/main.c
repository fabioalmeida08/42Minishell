/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:10:15 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/05 16:56:35 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	init_env(envp, &sh);
	init_builtin(&sh);
	sh.input = NULL;
	sh.head_tokens = NULL;
	sh.head_ast = NULL;
	if (isatty(STDIN_FILENO))
	{
		setup_interactive_parent_signals();
		interactive_mode(&sh);
	}
	else
		non_interactive_mode();
	return (0);
}
