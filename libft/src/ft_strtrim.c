/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:40:12 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/22 14:07:56 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	char_in_set(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	get_start(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!char_in_set(set, s[i]))
			return (i);
		i++;
	}
	return (0);
}

static size_t	get_end(const char *s, const char *set)
{
	size_t	end;

	end = ft_strlen(s);
	if (end <= 0)
		return (0);
	while (end--)
	{
		if (!char_in_set(set, s[end]))
			return (end);
	}
	return (end);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	start = get_start(s1, set);
	end = get_end(s1, set);
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}
