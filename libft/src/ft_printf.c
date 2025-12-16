/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:49:15 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/30 18:51:36 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handler(va_list arg, char specifier)
{
	int		counter;
	char	fd;

	fd = 1;
	counter = 0;
	if (specifier == 'c')
		counter += char_handler(arg, fd);
	if (specifier == 's')
		counter += str_handler(arg, fd);
	if (specifier == 'd' || specifier == 'i')
		counter += nbr_handler(arg, fd);
	if (specifier == 'x' || specifier == 'X')
		counter += hex_handler(arg, fd, specifier);
	if (specifier == 'u')
		counter += unbr_handler(arg, fd);
	if (specifier == 'p')
		counter += ptr_handler(arg, fd);
	if (specifier == '%')
	{
		ft_putchar_fd('%', fd);
		counter++;
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	size_t	count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_handler(args, format[++i]);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i++], 1);
			count++;
		}
	}
	va_end(args);
	return (count);
}
