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

void	display_arrays(char ***arrays)
{
	int		ct;
	int		i;

	ct = -1;
	while (arrays[++ct])
	{
		i = 0;
		while (arrays[ct][i])
			printf("[ %s ]\n", arrays[ct][i++]);
		write(1, "\n", 1);
	}
}

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

int		redirect_in_args(char **array)
{
	while (*array)
	{
		if (!ft_strcmp(*array, ">") || !ft_strcmp(*array, "<"))
			return (1);
		array++;
	}
	return (0);
}

void	loop_pipe(t_all *all, char ***pipe2exec)
{
	pid_t	pid;
	int		p[2];
	int		dup_stdin;
	char	*file;
	int		redir;

	file = NULL;
	while (*pipe2exec)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			ft_putstr("fork() error\n");
		else if (pid == 0)
		{
			dup2(dup_stdin, 0);
			if (*(pipe2exec + 1))
				dup2(p[1], 1);
			close(p[0]);
			if (redirect_in_args(*pipe2exec))
				file = redirected_in_args(*pipe2exec, &redir);
			if (execve(create_good_path(all, *pipe2exec[0]), \
								*pipe2exec, all->dupenv) == -1)
				ft_putstr("execve() error\n");
			// if (redirect_in_args(*pipe2exec))
				// exec_redirect(all, create_good_path(all, *pipe2exec[0]), *pipe2exec, file, redir);
			exit(21);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			dup_stdin = p[0];
			pipe2exec++;
		}
	}
}

void	create_pipe(t_all *all, char *cmd)
{
	char	***pipe2exec;

	pipe2exec = create_pipe_arrays(ft_strsplit(cmd, '|'));
	// display_arrays(pipe2exec);
	loop_pipe(all, pipe2exec);
}

/*
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
	// ft_putstr("PIPE ARRAY\n");
	// display_array(all->pipe);
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
			// if ((size_t)i < ft_tablen(all->pipe))
			// {
			// 	// ft_putstr("OK\n");
			// 	exec_pipe_process(all, goodpath, args);
			// }
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
	// ft_putstr("PIPE ARGS\n");
	// display_array(args);
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
*/