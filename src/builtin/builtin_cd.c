/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:48:54 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/06 11:45:22 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void update_work_dirs(t_shell *sh, char *old_pwd)
{
	char cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		perror("minishell: cd: error geting current dir");
		return ;
	}
	if (old_pwd)
		update_env_var(sh->env_list, "OLDPWD", old_pwd);
	update_env_var(sh->env_list, "PWD", cwd);
}

bool	change_home(t_shell *sh)
{
	char *home_dir;
	char	*cwd;

	home_dir = get_env_value(sh->env_list, "HOME");
	cwd = get_env_value(sh->env_list, "PWD");

	if (chdir(home_dir) != 0)
	{
		ft_putstr_fd("minishell: cd: cannot find HOME", 2);
		sh->exit_status = 1;
	}
	else
	{
		update_work_dirs(sh, cwd);
		sh->exit_status = 0;
	}
	return (true);
}


void	builtin_cd(char **cmd, t_shell *sh)
{
	char	*target_dir;
	char	old_pwd[4096];

	if (getcwd(old_pwd, 4096) == NULL)
		ft_strlcpy(old_pwd, get_env_value(sh->env_list, "PWD"), 4096);
	if (!cmd[1] || ft_strcmp(cmd[1], "~"))
	{
		change_home(sh);
		return ;
	}
	target_dir = cmd[1];
	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cmd[1]);
		sh->exit_status = 1;
	}
	else
	{
		update_work_dirs(sh, old_pwd);
		sh->exit_status = 0;
	}
}
