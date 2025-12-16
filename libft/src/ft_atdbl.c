/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atdbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:57:09 by fabialme          #+#    #+#             */
/*   Updated: 2025/10/01 14:57:42 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atdbl(const char *nptr)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	sign = 1;
	pow = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign *= -1;
	while (*nptr != '.' && *nptr)
		integer_part = (integer_part * 10) + (*nptr++ - 48);
	if (*nptr == '.')
		nptr++;
	while (*nptr)
	{
		pow /= 10;
		fractional_part = fractional_part + (*nptr++ - 48) * pow;
	}
	return ((integer_part + fractional_part) * sign);
}
