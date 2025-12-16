/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:44:03 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/22 11:19:33 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	str_len;
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (!str_len)
		return (ft_calloc(1, 1));
	dup = ft_calloc(str_len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < str_len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
