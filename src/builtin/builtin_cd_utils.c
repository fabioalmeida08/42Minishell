/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:22:13 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/06 11:34:56 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// void	builtin_cd(char **cmd, t_shell *sh)
// void	change_home(t_shell *sh)
// {
// 	char *home_dir;
// 	char	*cwd;
//
// 	home_dir = get_env_value(sh->env_list,"HOME");
// 	cwd = get_env_value(sh->env_list, "PWD");
//
// 	if (chdir(home_dir) != 0)
// 	{
// 			ft_putstr_fd("minishell: cd: cannot find HOME", 2);
// 			sh->exit_status = 1;
// 	}
// 	else
// 	{
// 			update_work_dirs(sh, cwd);
// 			sh->exit_status = 0;
// 	}
// }
