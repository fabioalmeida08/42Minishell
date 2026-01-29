/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:42:57 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/29 11:44:22 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_validate_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

void	update_work_dirs(t_shell *sh, char *old_pwd)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		perror("cd: error geting current dir");
		return ;
	}
	if (old_pwd)
		update_env_var(sh->env_list, "OLDPWD", old_pwd);
	update_env_var(sh->env_list, "PWD", cwd);
}

void	change_home(t_shell *sh, char *old_pwd)
{
	char	*home_dir;

	home_dir = get_env_value(sh->env_list, "HOME");
	if (!home_dir)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		sh->exit_status = 1;
		return ;
	}
	if (chdir(home_dir) != 0)
	{
		ft_putstr_fd("minishell: cd: cannot find HOME\n", 2);
		sh->exit_status = 1;
	}
	else
	{
		update_work_dirs(sh, old_pwd);
		sh->exit_status = 0;
	}
}

void	change_old_dir(t_shell *sh, char *old_pwd)
{
	char	*target_old;

	target_old = get_env_value(sh->env_list, "OLDPWD");
	if (!target_old)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		sh->exit_status = 1;
		return ;
	}
	if (chdir(target_old) != 0)
	{
		ft_putstr_fd("minishell: cd: cannot find dir\n", 2);
		sh->exit_status = 1;
	}
	else
	{
		update_work_dirs(sh, old_pwd);
		sh->exit_status = 0;
	}
}
