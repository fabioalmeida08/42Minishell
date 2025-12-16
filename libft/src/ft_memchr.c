/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:51:02 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/21 16:59:29 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	mem = (unsigned char *) s;
	while (i < n)
	{
		if (mem[i] == (unsigned char) c)
			return ((void *) mem + i);
		i++;
	}
	return (NULL);
}
