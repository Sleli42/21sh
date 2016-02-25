/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 11:42:27 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/05 11:42:28 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		good_access(char *bin)
{
	if (access(bin, F_OK) == 0)
		if (access(bin, X_OK) == 0)
			return (1);
	return (0);
}

char	*create_path(char *path, char *bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp, bin);
	return (tmp);
}

void	write_error(char *cmd_error)
{
	ft_putstr("Command: '");
	ft_putstr(cmd_error);
	ft_putstr("' not found\n");
}

void	exec_right_binary(t_all *all, char **argv_bin)
{
	int		ct;
	int		stop;
	char	*bin_tmp;

	ct = 0;
	stop = 0;
	bin_tmp = NULL;
	// ft_putstr("\n\tARGV_BIN ARRAY\n\n");
	// display_array(argv_bin);
	while (all->path2exec[ct])
	{
		bin_tmp = create_path(all->path2exec[ct], argv_bin[0]);
		if (good_access(bin_tmp))
		{
			stop = 1;
			exec_binary(bin_tmp, argv_bin, all->dupenv);
			break ;
		}
		ft_strdel(&bin_tmp);
		ct++;
	}
	if (!stop)
		write_error(argv_bin[0]);
}

void	exec_binary(char *bin, char **argv_bin, char **env)
{
	int		buff;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error("FORK");
	if (pid == 0)
		if (execve(bin, argv_bin, env) == -1)
			error("EXECVE");
	if (pid > 0)
		waitpid(pid, &buff, 0);
}
