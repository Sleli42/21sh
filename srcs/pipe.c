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

char	*create_good_path(t_all *all, char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (all->path2exec[i])
	{
		tmp = ft_strjoin(all->path2exec[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (good_access(tmp))
			return (tmp);
		i++;
	}
	return (NULL);
}

int		check_redirect(char *s)
{
	while (*s)
	{
		if (*s == '>' || *s == '<')
			return (1);
		s++;
	}
	return (0);
}

char	*redirected_in_args(char **args, int *redir_type)
{
	int		i;
	char	*file_redir;

	i = 0;
	while (args[i])
	{
		if (ft_strequ(args[i], ">") || ft_strequ(args[i], ">>"))
		{
			if (ft_strequ(args[i], ">"))
				*redir_type = 1;
			else
				*redir_type = 2;
			free(args[i]);
			file_redir = args[i + 1];
			args[i] = NULL;
			args[i + 1] = NULL;
			return (file_redir);
		}
		i++;
	}
	return (NULL);
}

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

int		open_file(char *file, int redir)
{
	int		fd;

	fd = 0;
	if (file)
	{
		if (redir == 1)
		{
			if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
				write(1, "open err0r\n", 11);
		}
		else
		{
			if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
				write(1, "open err0r\n", 11);
		}
	}
	return (fd);
}

void	exec_redirect(t_all *all, char *cmd, char **args, char *file, int redir)
{
	pid_t	child;
	int		fd;

	fd = open_file(file, redir);
	if (cmd == NULL)
		return ;
	if ((child = fork()) == -1)
		write(1, "fork  error\n", 11);
	if (child == 0)
	{
		if (file != NULL)
		{
			dup2(fd, 1);
			close(fd);
		}
		if (execve(cmd, args, all->dupenv) == -1)
			write(1, "execve error\n", 13);
	}
	else
		wait(NULL);
}