/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:10:15 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/16 15:03:02 by bolegari         ###   ########.fr       */
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
	if (isatty(STDIN_FILENO))
	{
		setup_interactive_parent_signals();
		interactive_mode(&sh);
	}
	else
		non_interactive_mode(); 
	return (0);
}
