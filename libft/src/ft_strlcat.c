/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:43:59 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/22 18:50:01 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	if (!dst || size == 0)
		return (ft_strlen(src));
	dst_len = 0;
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	src_len = ft_strlen(src);
	if (size == 0 || dst_len >= size)
		return (dst_len + src_len);
	i = 0;
	j = dst_len;
	while (src[i] && i < (size - dst_len - 1))
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst_len + src_len);
}
