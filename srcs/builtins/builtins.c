/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:06:54 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/14 10:40:48 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	pwd_display(t_all *all, char *cmd)
{
	char	*pwd;
	char	*buff;

	(void)all;
	(void)cmd;
	buff = NULL;
	pwd = getcwd(buff, 42);
	ft_putendl(pwd);
}

void	goto_dir(t_all *all, char *cmd)
{
	char	*buff;

	buff = NULL;
	all->oldpwd = getcwd(buff, 42);
	all->oldpwd = ft_strjoin(all->oldpwd, "/");
	cmd = ft_strdup(cmd + 3);
	if (cmd[0] == '\0')
		cmd = ft_strdup("/nfs/zfs-student-5/users/2014/lubaujar/");
	else if (cmd[0] == '-')
		cmd = ft_strdup(find_env_arg(all, "OLDPWD") + 7);
	if (access(cmd, F_OK) == 0)
	{
		if (chdir(cmd) == -1)
			error("DIR");
		update_oldpwd(all);
	}
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

char			*obtain_history_p(char *history)
{
	char		*ret;

	return ((ret = *history == ':' ? ++history : obtain_history_p(++history)));
}

int				get_arg(char *p_cmd)
{
	int			ret;

	ret = 0;
	while (*p_cmd)
	{
		if (*p_cmd++ == ' ')
			ret++;
		if (*p_cmd && ret && ft_isascii(*p_cmd) && *p_cmd != ' ')
			ret++;
	}
	return (ret);
}

char			*first_cmd(char *cmd)
{
	char		*format;
	int			i;

	i = 0;
	format = NULL;
	while(cmd[i] && cmd[i] != ' ')
		i++;
	return ((format = ft_strsub(cmd, 0, i)));
}

int				get_index(char *p_cmd)
{
	int			ret;
	char		*format;

	ret = 0;
	while (ft_isdigit(p_cmd[ret]))
		ret++;
	format = ft_strsub(p_cmd, 0, ret);
	ret = ft_atoi(format);
	ft_strdel(&format);
	return (ret - 1);
}

void			join_params(char **p_cmd, char *orig_cmd)
{
	char		*format;

	format = NULL;
	while (*orig_cmd && *orig_cmd != ' ')
		orig_cmd++;
	format = ft_strjoin((*p_cmd), orig_cmd);
	ft_strdel(p_cmd);
	(*p_cmd) = format;
}

void			built_mark(t_all *all, char *cmd)
{
	char		**history;
	int			p_index;
	char		*p_cmd;
	int			params;

	(void)all;
	(void)cmd;
	all->p_mark = NULL;
	p_index = all->index_history;
	params = get_arg(cmd);
	p_cmd = params > 1 ? first_cmd(cmd + 1) : cmd + 1;
	if (!p_cmd)
		return ;
	history = parse_history();
	if (!history)
		return(ft_putstr("NO HISTORY\n"));
	if (ft_isdigit((int)(*p_cmd)))
	{
		p_index = get_index(p_cmd);
		p_cmd = p_index <= all->index_history && p_index >= 0 ? \
				ft_strdup(obtain_history_p(history[p_index])) : NULL;
		if (!p_cmd)
			return ;
		p_cmd[ft_strlen(p_cmd)] = 0;
		all->pos_history = p_index + 1;
		if (params > 1)
			join_params(&p_cmd, cmd);
		realloc_termcaps_cmd(all, p_cmd);
		all->p_mark = params > 1 ? NULL : all->cmd_termcaps;
		all->cmd = p_cmd;
		return (params > 1 ? create_and_exec_command(all) : loop(all));
	}
	while (p_index >= 0)
	{
		if (*p_cmd && history[p_index] && !ft_strncmp(p_cmd, obtain_history_p(history[p_index]), ft_strlen(p_cmd)))
		{
			p_cmd = ft_strdup(obtain_history_p(history[p_index]));
			p_cmd[ft_strlen(p_cmd)] = 0;
			if (params > 1)
				join_params(&p_cmd, cmd);
			realloc_termcaps_cmd(all, p_cmd);
			all->p_mark = params > 1 ? NULL : all->cmd_termcaps;
			all->cmd = p_cmd;
			return (params > 1 ? create_and_exec_command(all) : loop(all));
		}
		p_index--;
	}
	return (ft_putendl("\n\n42sh: event not found\n\n"));
}

void	free_all(t_all *all, char *cmd)
{
	(void)cmd;
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
	close(all->fd_history);
	free(all);
	all = NULL;
	ft_putendl("exit");
	exit(21);
}