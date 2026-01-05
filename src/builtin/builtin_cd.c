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
	update_env_var(sh->env_list, "PWD", old_pwd);
}

//TODO: refactorar, apos dar cd o variavel de env PWD não está sendo atualizada
//averiguar esse comportamento
void	builtin_cd(char **cmd, t_shell *sh)
{
    char    *target_dir;
    char    old_pwd[4096];

    // 1. Salva o diretório atual ANTES de mudar (para ser o futuro OLDPWD)
    if (getcwd(old_pwd, 4096) == NULL)
        // Se falhar (ex: diretório atual foi deletado), tentamos pegar do env
        ft_strlcpy(old_pwd, get_env_value(sh->env_list, "PWD"), 4096);

    // 2. Define o alvo
    if (!cmd[1]) // Caso: cd (apenas)
    {
        target_dir = get_env_value(sh->env_list, "HOME");
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            sh->exit_status = 1;
            return ;
        }
    }
    else if (ft_strncmp(cmd[1], "-", 2) == 0) // Caso: cd -
    {
        target_dir = get_env_value(sh->env_list, "OLDPWD");
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            sh->exit_status = 1;
            return ;
        }
        // "cd -" geralmente imprime para onde foi
        printf("%s\n", target_dir); 
    }
    else // Caso: cd caminho
    {
        target_dir = cmd[1];
    }

    // 3. Executa a syscall chdir
    if (chdir(target_dir) != 0)
    {
        // Se falhar, imprimimos o erro padrão (ex: No such file or directory)
        ft_putstr_fd("minishell: cd: ", 2);
        perror(cmd[1]);
        sh->exit_status = 1;
    }
    else
    {
        // 4. Se sucesso, atualiza as variáveis de ambiente
        update_work_dirs(sh, old_pwd);
        sh->exit_status = 0;
    }
}
