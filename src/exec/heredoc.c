/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:09:27 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/28 19:27:08 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_eof_or_signal(char *line)
{
	if (!line)
	{
		if (g_signal_status == SIGINT)
		{
			open("/dev/tty", O_RDONLY);
			return (1);
		}
		ft_putstr_fd("minishell: warning: here-document delimited by EOF\n", 2);
		return (1);
	}
	return (0);
}

static void	process_line_content(int fd, char *line, bool expand, t_shell *sh)
{
	char	*tmp;

	if (expand)
	{
		tmp = expand_heredoc_line(line, sh);
		free(line);
		line = tmp;
	}
	ft_putendl_fd(line, fd);
	free(line);
}

static void	write_heredoc_loop(int fd, char *delim, bool expand, t_shell *sh)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (handle_eof_or_signal(line))
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		process_line_content(fd, line, expand, sh);
	}
}

int	process_heredoc(char *delimiter, bool expand, t_shell *sh)
{
	int		fd;
	char	*filename;
	int		read_fd;

	filename = "/tmp/.mshell_heredoc_tmp";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc open failed"), -1);
	signal(SIGINT, heredoc_sigint_handler);
	write_heredoc_loop(fd, delimiter, expand, sh);
	close(fd);
	if (g_signal_status == SIGINT)
	{
		free_all_structs(sh);
		exit(130);
	}
	read_fd = open(filename, O_RDONLY);
	unlink(filename);
	return (read_fd);
}
