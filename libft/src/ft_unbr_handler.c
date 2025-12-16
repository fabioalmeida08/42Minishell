/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbr_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:27:18 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/30 18:51:51 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned int	nbr;

	nbr = n;
	if (nbr > 0 && nbr <= 9)
		ft_putchar_fd(nbr + '0', fd);
	else
	{
		ft_putunbr_fd(nbr / 10, fd);
		ft_putunbr_fd(nbr % 10, fd);
	}
}

int	unbr_handler(va_list args, int fd)
{
	size_t			nbr_size;
	unsigned int	nbr;
	unsigned int	nbr_copy;

	nbr = va_arg(args, unsigned int);
	nbr_copy = nbr;
	nbr_size = 0;
	if (nbr == 0)
		nbr_size = 1;
	while (nbr > 0)
	{
		nbr_size++;
		nbr /= 10;
	}
	ft_putunbr_fd(nbr_copy, fd);
	return (nbr_size);
}
