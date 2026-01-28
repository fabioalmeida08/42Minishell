/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:25:40 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/28 19:25:54 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*strjoin_free_s1(char *s1, char *s2)
{
	char	*new_str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = "";
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

static char	*get_var_val(char *key, t_shell *sh)
{
	char	*val;
	char	*tmp;

	tmp = get_env_value(sh->env_list, key);
	if (tmp)
		val = ft_strdup(tmp);
	else
		val = ft_strdup("");
	return (val);
}

static char	*extract_var_value(char *line, int *i, t_shell *sh)
{
	int		start;
	char	*key;
	char	*val;

	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(sh->exit_status));
	}
	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	key = ft_substr(line, start, *i - start);
	val = get_var_val(key, sh);
	free(key);
	return (val);
}

char	*expand_heredoc_line(char *line, t_shell *sh)
{
	int		i;
	char	*final;
	char	*val;
	char	tmp[2];

	i = 0;
	final = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '_' || line[i + 1] == '?'))
		{
			val = extract_var_value(line, &i, sh);
			final = strjoin_free_s1(final, val);
			free(val);
		}
		else
		{
			tmp[0] = line[i++];
			tmp[1] = '\0';
			final = strjoin_free_s1(final, tmp);
		}
	}
	return (final);
}
