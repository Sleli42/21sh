/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:06:54 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:09:26 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void			pwd_display(t_all *all, char *cmd)
{
	char		*pwd;
	char		*buff;

	(void)all;
	(void)cmd;
	buff = NULL;
	if ((pwd = getcwd(buff, 42)) == NULL)
		return ;
	ft_putendl(pwd);
}

void			write_error_goto_dir(char *err)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putstr(err);
	ft_putchar('\n');
}

void			goto_dir(t_all *all, char *cmd)
{
	char		*buff;

	buff = NULL;
	(all->oldpwd && *all->oldpwd) ? ft_strdel(&all->oldpwd) : NULL;
	all->oldpwd = ft_strdup(getcwd(buff, 512));
	all->oldpwd = (ft_strcmp(all->oldpwd, "/")) \
			? ft_strjoin(all->oldpwd, "/") : all->oldpwd;
	cmd += 3;
	if (*cmd == '\0')
		cmd = find_env_arg(all, "HOME") + 5;
	if (*cmd == '~')
		cmd = ft_strjoin(find_env_arg(all, "HOME") + 5, cmd + 1);
	if (*cmd == '-')
	{
		cmd = find_env_arg(all, "OLDPWD") + 7;
		cmd = !cmd || !*cmd ? ft_strdup("/") : cmd;
	}
	if (access(cmd, F_OK) == 0)
	{
		if (chdir(cmd) == -1)
			error("DIR");
		update_oldpwd(all);
	}
	else
		write_error_goto_dir(cmd);
}

void			built_history(t_all *all, char *cmd)
{
	int			fd;
	int			ret;
	char		buf[MAXLEN];

	(void)all;
	(void)cmd;
	if ((fd = open(".21sh_history", O_RDONLY)) == -1)
		return (error("OPEN"));
	while ((ret = read(fd, buf, MAXLEN)) > 0)
	{
		buf[ret] = 0;
		ft_putstr(buf);
	}
	close(fd) == -1 ? ft_putendl("close ERROR") : ft_putchar(0);
}

void			free_all(t_all *all, char *cmd)
{
	reset_term();
	close(all->fd_history);
	free(all);
	all = NULL;
	ft_putendl("exit");
	(cmd + 5 && ft_isdigit(*(cmd + 5))) \
		? exit(ft_atoi(cmd + 5)) : exit(1);
}
