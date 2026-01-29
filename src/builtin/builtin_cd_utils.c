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

static bool	cd_validate_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (false);
	}
	return (true);
}

static void	update_work_dirs(t_shell *sh, char *old_pwd)
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

bool	change_home(t_shell *sh)
{
	char	*home_dir;
	char	*cwd;

	home_dir = get_env_value(sh->env_list, "HOME");
	cwd = get_env_value(sh->env_list, "PWD");
	if (chdir(home_dir) != 0)
	{
		ft_putstr_fd("cd: cannot find HOME\n", 2);
		sh->exit_status = 1;
	}
	else
	{
		update_work_dirs(sh, cwd);
		sh->exit_status = 0;
	}
	return (true);
}

void	change_directory_path(char *path, char *old_pwd, t_shell *sh)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		sh->exit_status = 1;
	}
	else
	{
		update_work_dirs(sh, old_pwd);
		sh->exit_status = 0;
	}
}

void	save_current_dir(t_shell *sh, char *buffer)
{
	if (getcwd(buffer, 4096) == NULL)
		ft_strlcpy(buffer, get_env_value(sh->env_list, "PWD"), 4096);
}
