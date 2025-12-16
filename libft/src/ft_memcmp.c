/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:52:30 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/21 16:54:12 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*foo;
	unsigned char	*bar;
	size_t			i;

	foo = (unsigned char *) s1;
	bar = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (foo[i] != bar[i])
			return (foo[i] - bar[i]);
		i++;
	}
	return (0);
}
