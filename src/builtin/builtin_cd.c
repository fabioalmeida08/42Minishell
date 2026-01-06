/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:48:54 by fabialme          #+#    #+#             */
/*   Updated: 2026/01/05 16:51:40 by fabialme         ###   ########.fr       */
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

void	builtin_cd(char **cmd, t_shell *sh)
{
    char    *target_dir;
    char    old_pwd[4096];

    if (getcwd(old_pwd, 4096) == NULL)
        ft_strlcpy(old_pwd, get_env_value(sh->env_list, "PWD"), 4096);
    if (!cmd[1])
    {
        target_dir = get_env_value(sh->env_list, "HOME");
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            sh->exit_status = 1;
            return ;
        }
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
