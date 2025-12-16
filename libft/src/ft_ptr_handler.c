/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:23:59 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/30 19:04:55 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putptr(unsigned long long nbr, char *base, int fd)
{
	int	i;

	i = 0;
	if (nbr >= 16)
		i += ft_putptr(nbr / 16, base, fd);
	i += write(fd, &base[nbr % 16], 1);
	return (i);
}

int	ptr_handler(va_list args, int fd)
{
	unsigned long long	nbr;
	int					i;

	nbr = va_arg(args, unsigned long long);
	if (nbr == 0)
		return (write(fd, "(nil)", 5));
	i = write(fd, "0x", 2);
	i += ft_putptr(nbr, HEX_BASE, fd);
	return (i);
}
