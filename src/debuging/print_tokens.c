/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:23:54 by marvin            #+#    #+#             */
/*   Updated: 2025/12/29 17:23:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_node_type(t_token *current)
{
	if (current->type == TK_WORD)
		printf("WORD");
	else if (current->type == TK_PIPE)
		printf("PIPE");
	else if (current->type == TK_REDIR_IN)
		printf("REDIR_IN");
	else if (current->type == TK_REDIR_OUT)
		printf("REDIR_OUT");
	else if (current->type == TK_REDIR_APPEND)
		printf("REDIR_APPEND");
	else if (current->type == TK_REDIR_HEREDOC)
		printf("HEREDOC");
	else if (current->type == TK_OR)
		printf("OR");
	else if (current->type == TK_AND)
		printf("AND");
	else if (current->type == TK_PAREN_OPEN)
		printf("PAREN_OPEN");
	else if (current->type == TK_PAREN_CLOSE)
		printf("PAREN_CLOSE");
	else
		printf("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!tokens)
	{
		printf("Nenhum token\n");
		return ;
	}
	while (current)
	{
		printf("[");
		print_node_type(current);
		if (current->value)
			printf(": %s] -> ", current->value);
		else
			printf(": %s] -> ", "(null)");
		current = current->next;
	}
	printf("NULL\n");
}
