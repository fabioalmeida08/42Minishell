/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:40:07 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/27 16:48:25 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_numeric (char *ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		if (!ft_isdigit(ptr[i++]))
			return false;
	return true;
}
//TODO: refatorar em varias funcoes para ficar de acordo com a norma
//e lembrar de arruma a mensagem de cd e exec quando o comando nao existe
void	builtin_exit(char **cmd, t_shell *sh)
{
	int i;

	i = 1;
	if (!cmd[i])
	{
		sh->running = false;
		return ;
	}
	while (cmd[i])
	{
		if (!is_numeric(cmd[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": numeric arguments required\n", 2);
			return ;
		}
		i++;
	}
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	i = 1;
	if (!is_numeric(cmd[i]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[i], 2);
		ft_putstr_fd(" numeric arguments required\n", 2);
		return ;
	}
	sh->exit_status = ft_atoi(cmd[i]);
}
