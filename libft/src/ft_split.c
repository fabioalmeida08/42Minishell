/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:35:34 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/23 09:23:29 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	word_count(const char *s, char c)
{
	size_t	words;
	char	in_word;

	words = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			words++;
			in_word = 1;
		}
		if (*s == c)
			in_word = 0;
		s++;
	}
	return (words);
}

static size_t	get_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*create_word(const char *s, char c)
{
	char	*str;
	size_t	len;

	len = get_word_len(s, c);
	str = ft_substr(s, 0, len);
	return (str);
}

static char	**fill_array(char **arr, const char *s, char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		while (*s == c)
			s++;
		arr[i] = create_word(s, c);
		if (!arr[i])
		{
			while (i)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		s += get_word_len(s, c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	arr_size;

	arr_size = word_count(s, c);
	arr = ft_calloc(sizeof(char *), (arr_size + 1));
	if (!arr)
		return (NULL);
	return (fill_array(arr, s, c, arr_size));
}
