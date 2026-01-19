/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:23:44 by bolegari          #+#    #+#             */
/*   Updated: 2026/01/19 15:58:47 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	args_len(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

void	append_all(char ***dst, char **src)
{
	char	**new;
	int		len_dst;
	int		i;

	if (!src || !src[0])
		return ;
	len_dst = args_len(*dst);
	new = ft_calloc(len_dst + args_len(src) + 1, sizeof(char *));
	if (!new)
		return ;
	i = 0;
	while (i < len_dst)
	{
		new[i] = (*dst)[i];
		i++;
	}
	i = 0;
	while (src[i])
	{
		new[len_dst + i] = src[i];
		i++;
	}
	free(*dst);
	*dst = new;
}

char	*ft_charjoin_free(char *s, char c)
{
	char	*new;
	size_t	len;

	if (!s)
	{
		new = malloc(2);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	len = ft_strlen(s);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return (new);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	free(s1);
	return (new);
}

void	append_one(char ***args, char *arg)
{
	char	*tmp[2];

	if (!arg)
		return ;
	tmp[0] = arg;
	tmp[1] = NULL;
	append_all(args, tmp);
}
