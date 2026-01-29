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

static void	change_directory_path(char *path, t_shell *sh, char *old_pwd)
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

// Helper para salvar o diretório atual de forma segura
static void	get_current_pwd_safe(t_shell *sh, char *buffer)
{
	if (getcwd(buffer, 4096) == NULL)
		ft_strlcpy(buffer, get_env_value(sh->env_list, "PWD"), 4096);
}

void	builtin_cd(char **cmd, t_shell *sh)
{
	char	old_pwd[4096];

	if (!cd_validate_args(cmd))
	{
		sh->exit_status = 1;
		return ;
	}
	get_current_pwd_safe(sh, old_pwd);
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
		change_home(sh, old_pwd);
	else if (ft_strcmp(cmd[1], "-") == 0)
		change_old_dir(sh, old_pwd);
	else
		change_directory_path(cmd[1], sh, old_pwd);
}
