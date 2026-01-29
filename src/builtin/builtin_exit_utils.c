/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:10:49 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/29 14:11:39 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_atoll_checked(const char *str, long long *out)
{
	unsigned long long	res;
	int					sign;
	int					i;

	if (!is_digit_str((char *)str))
		return (false);
	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (res > (9223372036854775807ULL / 10) || \
			(res == (9223372036854775807ULL / 10)
				&& (str[i] - '0') > 7 + (sign == -1)))
			return (false);
		res = res * 10 + (str[i++] - '0');
	}
	*out = (long long)(res * sign);
	return (true);
}
