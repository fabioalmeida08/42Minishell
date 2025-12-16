/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:29:42 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/11 16:18:56 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

//TODO: remover func debug
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
		switch (current->type)
		{
			case TK_WORD:
				printf("WORD");
				break ;
			case TK_PIPE:
				printf("PIPE");
				break ;
			case TK_REDIR_IN:
				printf("REDIR_IN");
				break ;
			case TK_REDIR_OUT:
				printf("REDIR_OUT");
				break ;
			case TK_REDIR_APPEND:
				printf("REDIR_APPEND");
				break ;
			case TK_REDIR_HEREDOC:
				printf("HEREDOC");
				break ;
			default:
				printf("UNKNOWN");
		}
		printf(": %s] -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}
