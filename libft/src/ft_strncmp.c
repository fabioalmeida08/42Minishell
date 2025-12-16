/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:47:14 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/21 16:50:25 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*foo;
	unsigned char	*bar;

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
