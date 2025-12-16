/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:39:02 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/25 11:55:57 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	unsigned char	*tmp;
	size_t			i;

	if (!nmemb || !size)
		return (malloc(1));
	if (size && nmemb > (size_t) - 1 / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	tmp = (unsigned char *) mem;
	i = 0;
	while (i < (nmemb * size))
		tmp[i++] = '\0';
	return (mem);
}
