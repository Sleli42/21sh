/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 12:07:10 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:43 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define PATH	(create_good_path(all, *pipe2exec[0]))

char	***create_pipe_arrays(char **split)
{
	char	***pipe2exec;
	size_t	ct;

	ct = -1;
	if (!(pipe2exec = (char ***)malloc(sizeof(char **) * ft_tablen(split) + 1)))
		error("MALLOC");
	while (split && ++ct < ft_tablen(split))
		pipe2exec[ct] = ft_strsplit(ft_epur_str(split[ct]), ' ');
	pipe2exec[ct] = NULL;
	return (pipe2exec);
}

void	loop_pipe_extended(t_all *all, char ***pipe2exec, \
										int dup_stdin, int p[2])
{
	int		dup_stdout;

	*pipe2exec += (*pipe2exec[0][0] == '&') ? 1 : 0;
	dup2(dup_stdin, 0);
	if (*(pipe2exec + 1))
		dup2(p[1], 1);
	close(p[0]);
	if (redirect_in_args(*pipe2exec))
	{
		dup_stdout = dup(1);
		*pipe2exec = modify_pipe_array(all, *pipe2exec);
		dup2(all->fd2open, 1);
		close(all->fd2open);
		if (execve(PATH, *pipe2exec, all->dupenv) == -1)
			ft_putstr("execve() error\n");
		dup2(dup_stdout, 1);
		close(dup_stdout);
	}
	else
	{
		if (execve(PATH, *pipe2exec, all->dupenv) == -1)
			ft_putstr("execve() error\n");
	}
	exit(21);
}

void	loop_pipe(t_all *all, char ***pipe2exec)
{
	pid_t	pid;
	int		buff;
	int		p[2];
	int		dup_stdin;

	all->err_exec = 0;
	if (redirect_in_arrays(all, pipe2exec))
		all->fd2open = open_file(all->file2redir, 1);
	while (*pipe2exec)
	{
		pipe(p);
		all->redir_in_pipe = 0;
		if ((pid = fork()) == -1)
			ft_putstr("fork() error\n");
		else if (pid == 0)
			loop_pipe_extended(all, pipe2exec, dup_stdin, p);
		else
		{
			waitpid(pid, &buff, 0);
			all->err_exec = buff;
			close(p[1]);
			dup_stdin = p[0];
			pipe2exec++;
		}
	}
}

void	create_pipe(t_all *all, char *cmd)
{
	char	***pipe2exec;
	int		i;

	i = -1;
	pipe2exec = create_pipe_arrays(ft_strsplit(cmd, '|'));
	if (!check_pipe_error(pipe2exec))
		return ;
	else
		loop_pipe(all, pipe2exec);
	if (pipe2exec)
	{
		while (pipe2exec[++i])
			(pipe2exec[i]) ? del_array(&pipe2exec[i]) : NULL;
		pipe2exec = NULL;
	}
}
