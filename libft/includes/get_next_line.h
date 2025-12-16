/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:34:36 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/24 18:51:59 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif // !BUFFER_SIZE

# include "libft.h"

char	*get_next_line(int fd);
/*
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t elmt_qdt, size_t elmt_size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, char c);
*/
#endif // !GET_NEXT_LINE_H
