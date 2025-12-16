/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:01:52 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/21 18:01:52 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*haystack;
	const char	*needle;
	size_t		i;
	size_t		j;

	i = 0;
	if (!ft_strlen(little))
		return ((char *) big);
	while (*big && i < len)
	{
		haystack = big;
		needle = little;
		j = i;
		while (*haystack && *needle && *haystack == *needle && j++ < len)
		{
			haystack++;
			needle++;
		}
		if (*needle == '\0')
			return ((char *) big);
		i++;
		big++;
	}
	return (NULL);
}
