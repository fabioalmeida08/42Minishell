/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:09:27 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/22 10:09:52 by fabialme         ###   ########.fr       */
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

static char	*extract_var_value(char *line, int *i, t_shell *sh)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;

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
	tmp = get_env_value(sh->env_list, key);
	if (tmp)
		val = ft_strdup(tmp);
	else
		val = ft_strdup("");
	free(key);
	return (val);
}

static char	*expand_heredoc_line(char *line, t_shell *sh)
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

static void	write_heredoc_loop(int fd, char *delim, bool expand, t_shell *sh)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by EOF\n", 2);
			break ;
		}
		if (ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		if (expand)
		{
			tmp = expand_heredoc_line(line, sh);
			free(line);
			line = tmp;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	process_heredoc(char *delimiter, bool expand, t_shell *sh)
{
	int		fd;
	char	*filename;

	filename = "/tmp/.mshell_heredoc_tmp";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: heredoc open");
		return (-1);
	}
	write_heredoc_loop(fd, delimiter, expand, sh);
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	return (fd);
}
