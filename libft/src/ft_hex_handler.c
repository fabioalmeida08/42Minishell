/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:41:11 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/30 18:51:23 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(unsigned int nbr, char *base, int fd)
{
	int	i;

	i = 0;
	if (nbr >= 16)
		i += ft_puthex(nbr / 16, base, fd);
	write(fd, &base[nbr % 16], 1);
	i++;
	return (i);
}

int	hex_handler(va_list args, int fd, char specifier)
{
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	if (specifier == 'x')
		return (ft_puthex(nbr, HEX_BASE, fd));
	if (specifier == 'X')
		return (ft_puthex(nbr, HEX_BASE_UPPER, fd));
	return (0);
}
