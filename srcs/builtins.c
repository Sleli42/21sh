/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:06:54 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/04 18:06:55 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	pwd_display(t_all *all)
{
	char	*pwd;
	char	*buff;

	(void)all;
	buff = NULL;
	pwd = getcwd(buff, 42);
	ft_putendl(pwd);
}

void	goto_dir(t_all *all)
{
	char	*buff;

	buff = NULL;
	all->oldpwd = getcwd(buff, 42);
	all->oldpwd = ft_strjoin(all->oldpwd, "/");
	all->cmd = ft_strdup(all->cmd + 3);
	if (all->cmd[0] == '\0')
		all->cmd = ft_strdup("/nfs/zfs-student-5/users/2014/lubaujar/");
	else if (all->cmd[0] == '-')
		all->cmd = ft_strdup(find_env_arg(all, "OLDPWD") + 7);
	if (access(all->cmd, F_OK) == 0)
	{
		if (chdir(all->cmd) == -1)
			error("DIR");
		update_oldpwd(all);
	}
}

void	free_all(t_all *all)
{
	// while (all->env->lenght-- != 0)
	// 	dlst_del_one(all->env, all->env->head->s);
	// if (all->path2exec != NULL)
	// 	del_array(&all->path2exec);
	// if (all->dupenv != NULL)
	// 	del_array(&all->dupenv);
	// if (all->cmd != NULL)
	// 	ft_strdel(&all->cmd);
	// if (all->redirect_cmd)
	// 	ft_strdel(&all->redirect_cmd);
	free(all);
	all = NULL;
	ft_putendl("exit");
	exit(21);
}