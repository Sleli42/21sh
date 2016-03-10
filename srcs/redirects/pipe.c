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
		if (*array[0] == '>' || *array[0] == '<')
			return (1);
		array++;
	}
	return (0);
}

int		redirect_in_arrays(t_all *all, char ***arrays)
{
	int			count;
	int			ct;

	count = 0;
	while (arrays[count])
	{
		ct = 0;
		while (arrays[count][ct])
		{
			if (arrays[count][ct][0] == '>')
			{
				all->file2redir = ft_strdup(arrays[count][ct + 1]);
				return (1);
			}
			ct++;
		}
		count++;
	}
	return (0);
}

char	**modify_pipe_array(t_all *all, char **array)
{
	char	**modify;
	int		count;

	count = 0;
	all->redir_in_pipe = 1;
	while (array[count] && array[count][0] != '>')
		count++;
	if (!(modify = (char**)malloc(sizeof(char*) * count + 1)))
		error("MALLOC");
	count = 0;
	while (array[count] && array[count][0] != '>')
	{
		modify[count] = ft_strdup(array[count]);
		count++;
	}
	all->file2redir = ft_strdup(array[count + 1]);
	modify[count] = NULL;
	return (modify);
}

void	loop_pipe(t_all *all, char ***pipe2exec)
{
	pid_t	pid;
	int		p[2];
	int		dup_stdin;
	int		dup_stdout;

	if (redirect_in_arrays(all, pipe2exec))
		all->fd2open = open_file(all->file2redir, 1);
	while (*pipe2exec)
	{
		pipe(p);
		all->redir_in_pipe = 0;
		if ((pid = fork()) == -1)
			ft_putstr("fork() error\n");
		else if (pid == 0)
		{
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
				if (execve(create_good_path(all, *pipe2exec[0]), \
								*pipe2exec, all->dupenv) == -1)
					ft_putstr("execve() error\n");
				dup2(dup_stdout, 1);
				close(dup_stdout);
			}
			else
			{
				if (execve(create_good_path(all, *pipe2exec[0]), \
								*pipe2exec, all->dupenv) == -1)
					ft_putstr("execve() error\n");
			}
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
	int 	i;

	i = -1;
	pipe2exec = create_pipe_arrays(ft_strsplit(cmd, '|'));
	loop_pipe(all, pipe2exec);
	if (pipe2exec)
	{
		while (pipe2exec[++i])
			(pipe2exec[i]) ? del_array(&pipe2exec[i]) : NULL;
		pipe2exec = NULL;
	}
}
