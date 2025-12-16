/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:24:53 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/22 18:43:09 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	get_nbr_size(int n)
{
	long	nbr;
	size_t	n_size;

	nbr = n;
	n_size = 0;
	if (nbr < 0)
	{
		n_size++;
		nbr *= -1;
	}
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr /= 10;
		n_size++;
	}
	return (n_size);
}

static char	*create_nptr(char *nptr, int n, size_t nptr_size)
{
	size_t	end;
	long	nbr;

	nbr = n;
	end = nptr_size - 1;
	if (nbr < 0)
	{
		nptr[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		nptr[0] = '0';
	while (nbr > 0)
	{
		nptr[end--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	nptr[nptr_size] = '\0';
	return (nptr);
}

char	*ft_itoa(int n)
{
	char	*nptr;
	size_t	nptr_size;

	nptr_size = get_nbr_size(n);
	nptr = ft_calloc(nptr_size + 1, sizeof(char));
	if (!nptr)
		return (NULL);
	return (create_nptr(nptr, n, nptr_size));
}
