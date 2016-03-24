/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:34:42 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:41 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

static void	write_error(char *cmd_error, int err)
{
	if (err == 1)
	{
		ft_putstr("42sh: ");
		ft_putstr(cmd_error);
		ft_putstr(": No such file or directory\n");
	}
	else if (err == 2)
	{
		ft_putstr("42sh: Command: '");
		ft_putstr(cmd_error);
		ft_putstr("' not found\n");
	}
}

void		exec_right_binary(t_all *all, char **argv_bin)
{
	char	*bin_tmp;

	bin_tmp = NULL;
	all->path2exec = NULL;
	all->path2exec = ft_strsplit(find_env_arg(all, "PATH") + 5, ':');
	if (!all->path2exec && !*all->path2exec)
	{
		write_error(argv_bin[0], 1);
		return ;
	}
	while (all->path2exec && *all->path2exec)
	{
		if (!(bin_tmp = create_path(*all->path2exec, argv_bin[0])))
			break ;
		if (bin_tmp && good_access(bin_tmp))
		{
			exec_binary(bin_tmp, argv_bin, all->dupenv);
			break ;
		}
		bin_tmp ? ft_strdel(&bin_tmp) : NULL;
		all->path2exec++;
	}
	!*all->path2exec ? write_error(argv_bin[0], 2) : ft_putchar(0);
	argv_bin ? del_array(&argv_bin) : NULL;
}

void		exec_binary(char *bin, char **argv_bin, char **env)
{
	int		buff;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error("FORK");
	if (pid == 0)
	{
		if (execve(bin, argv_bin, env) == -1)
			error("EXECVE");
		exit(1);
	}
	if (pid > 0)
		waitpid(pid, &buff, 0);
}
