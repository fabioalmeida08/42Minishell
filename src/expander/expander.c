/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:20:02 by marvin            #+#    #+#             */
/*   Updated: 2026/01/14 10:20:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expand_var(char *str, int *i, t_shell *sh)
{
	char	*name;
	char	*value;
	int		start;
	char	*res;

	if (str[++(*i)] == '?')
	{
		(*i)++;
		res = ft_itoa(sh->exit_status);
		return (res);
	}
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	name = ft_substr(str, start, *i - start);
	value = get_env_value(sh->env_list, name);
	free(name);
	if (!value)
		res = ft_strdup("");
	else
		res = ft_strdup(value);
	return (res);
}

static bool	state_updater(char c, t_quote *state)
{
	if ((c == '\'' && *state != Q_DOUBLE)
		|| (c == '"' && *state != Q_SINGLE))
	{
		if (*state == Q_NONE)
		{
			if (c == '\'')
				*state = Q_SINGLE;
			else
				*state = Q_DOUBLE;
		}
		else
			*state = Q_NONE;
		return (true);
	}
	return (false);
}

static void	handle_space(char **current_arg, char ***args, int *i)
{
	if (*current_arg)
	{
		append_one(args, *current_arg);
		*current_arg = NULL;
	}
	(*i)++;
}

static void	handle_dollar(char **current_arg, char ***args,
	t_quote state, char *expanded_var)
{
	int		i;
	char	**splited_var;

	i = 1;
	if (state == Q_DOUBLE)
		*current_arg = ft_strjoin_free(*current_arg, expanded_var);
	else
	{
		splited_var = ft_split(expanded_var, ' ');
		if (splited_var && splited_var[0])
		{
			*current_arg = ft_strjoin_free(*current_arg, splited_var[0]);
			append_one(args, *current_arg);
			*current_arg = NULL;
			while (splited_var[i])
			{
				append_one(args, ft_strdup(splited_var[i]));
				i++;
			}
		}
		if (splited_var)
			free_envp(splited_var);
	}
	free(expanded_var);
}

void	expand_and_remove_quotes(char *str, t_shell *sh, char ***args)
{
	int		i;
	t_quote	state;
	char	*current_arg;
	char	*expanded_var;

	i = 0;
	state = Q_NONE;
	current_arg = NULL;
	while (str[i])
	{
		if (state_updater(str[i], &state))
			i++;
		else if (str[i] == ' ' && state == Q_NONE)
			handle_space(&current_arg, args, &i);
		else if (str[i] == '$' && state != Q_SINGLE && str[i + 1])
		{
			expanded_var = expand_var(str, &i, sh);
			handle_dollar(&current_arg, args, state, expanded_var);
		}
		else
			current_arg = ft_charjoin_free(current_arg, str[i++]);
	}
	if (current_arg)
		append_one(args, current_arg);
}
