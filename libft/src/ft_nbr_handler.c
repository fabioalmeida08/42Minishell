/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:25:29 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/30 19:06:50 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_handler(va_list args, int fd)
{
	size_t	nbr_size;
	int		nbr;
	int		nbr_r;

	nbr = va_arg(args, int);
	nbr_r = nbr;
	nbr_size = 0;
	if (nbr < 0)
	{
		nbr_size++;
		nbr *= -1;
	}
	if (nbr == 0)
		nbr_size = 1;
	while (nbr != 0)
	{
		nbr_size++;
		nbr /= 10;
	}
	ft_putnbr_fd(nbr_r, fd);
	return (nbr_size);
}
