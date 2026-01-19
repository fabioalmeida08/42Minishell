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

static char	*ft_charjoin_free(char *s, char c)
{
	char	*new;
	size_t	len;

	if (!s)
	{
		new = malloc(2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	len = ft_strlen(s);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	free(s1);
	return (new);
}

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

static void	append_one(char ***args, char *arg)
{
	char	*tmp[2];

	if (!arg)
		return ;
	tmp[0] = arg;
	tmp[1] = NULL;
	append_all(args, tmp);
}

void	expand_and_remove_quotes(char *str, t_shell *sh, char ***args)
{
	int		i;
	t_quote	state;
	char	*current_arg;
	bool	arg_started;

	i = 0;
	state = Q_NONE;
	current_arg = NULL;
	arg_started = false;
	while (str[i])
	{
		if (state_updater(str[i], &state))
		{
			arg_started = true;
			i++;
		}
		else if (str[i] == ' ' && state == Q_NONE)
		{
			if (arg_started)
			{
				append_one(args, current_arg);
				current_arg = NULL;
				arg_started = false;
			}
			i++;
		}
		else if (str[i] == '$' && state != Q_SINGLE && str[i + 1])
		{
			char *expanded_var = expand_var(str, &i, sh);
			if (state == Q_DOUBLE)
				current_arg = ft_strjoin_free(current_arg, expanded_var);
			else
			{
				char **splited_var = ft_split(expanded_var, ' ');
				if (splited_var && splited_var[0])
				{
					current_arg = ft_strjoin_free(current_arg, splited_var[0]);
					append_one(args, current_arg);
					current_arg = NULL;
					int j = 0;
					while (splited_var[++j])
						append_one(args, ft_strdup(splited_var[j]));
				}
				if (splited_var)
					free_envp(splited_var);
			}
			free(expanded_var);
			arg_started = true;
		}
		else 
		{
			current_arg = ft_charjoin_free(current_arg, str[i++]);
			arg_started = true;
		}
	}
	if (arg_started)
	{
		append_one(args, current_arg);
		current_arg = NULL;
	}
}
