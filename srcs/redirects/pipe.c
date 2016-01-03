/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 12:07:10 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/05 12:07:12 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	create_pipe(t_all *all, char *cmd)
{
	char	**args;
	char	*goodpath;
	char	*file;
	int		i;
	int		redirect;
	pid_t	pid;

	i = 0;
	all->pipe = ft_strsplit(cmd, '|');
	file = NULL;
	if ((pid = fork()) == 0)
	{
		while (all->pipe[i])
		{
			all->pipe[i] = ft_epur_str(all->pipe[i]);
			args = ft_strsplit(all->pipe[i], ' ');
			goodpath = create_good_path(all, args[0]);
			if (check_redirect(all->pipe[i]))
				file = redirected_in_args(args, &redirect);
			if (ft_tablen(&all->pipe[i]) > 1)
				exec_pipe_process(all, goodpath, args);
			else
				exec_redirect(all, goodpath, args, file, redirect);
			del_array(&args);
			ft_strdel(&goodpath);
			ft_strdel(&file);
			i++; 
		}
		exit(0);
	}
	else
		wait(NULL);
}

void	exec_pipe_process(t_all *all, char *cmd, char **args)
{
	pid_t	child;
	int		fds[2];

	pipe(fds);
	if ((child = fork()) == -1)
		write(1, "fork  error\n", 11);
	else if (child == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		if (execve(cmd, args, all->dupenv) == -1)
			write(1, "execve error\n", 13);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		wait(NULL);
	}
}