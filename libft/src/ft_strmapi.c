/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:12:46 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/23 09:42:00 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	str_size;
	size_t	i;
	char	*n_str;

	str_size = ft_strlen(s);
	n_str = ft_calloc(str_size + 1, sizeof(*n_str));
	if (!n_str)
		return (NULL);
	i = 0;
	while (i < str_size)
	{
		n_str[i] = f(i, s[i]);
		i++;
	}
	return (n_str);
}
