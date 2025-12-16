/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:22:54 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/30 18:51:10 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_handler(va_list args, int fd)
{
	char	*string;

	string = va_arg(args, char *);
	if (!string)
		return (write(fd, "(null)", 6));
	ft_putstr_fd(string, fd);
	return (ft_strlen(string));
}
