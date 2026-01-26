/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:34:34 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/26 15:51:38 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	non_interactive_mode(t_shell *sh)
{
	ssize_t	read_bytes;
	size_t	len;

	len = 0;
	read_bytes = getline(&sh->input, &len, stdin);
	while (read_bytes != -1)
	{
		if (read_bytes > 0 && sh->input[read_bytes - 1] == '\n')
			sh->input[read_bytes - 1] = '\0';
		if (sh->input[0] != '\0')
		{
			sh->head_tokens = ft_tokenize(sh);
			sh->head_ast = parser_logical(sh->head_tokens, NULL, sh);
			if (sh->head_ast)
			{
				expand_ast(sh->head_ast, sh);
				setup_child_signals();
				execute_ast(sh->head_ast, sh);
			}
			free_internal_use_structs(sh);
		}
		read_bytes = getline(&sh->input, &len, stdin);
		set_signal_status(sh);
	}
	free_all_structs(sh);
}
