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

void	create_pipe(t_all *all, char *cmd)
{
	char	**args;
	char	*goodpath;
	int		i;
	pid_t	pid;

	i = 0;
	args = NULL;
	goodpath = NULL;
	//printf("to pipe: |%s|\n", cmd);
	all->pipe = ft_strsplit(cmd, '|');
	if ((pid = fork()) == 0)
	{
	while (all->pipe[i])
	{
		all->pipe[i] = ft_epur_str(all->pipe[i]);
		args = ft_strsplit(all->pipe[i], ' ');
		goodpath = create_good_path(all, args[0]);
		if (ft_tablen(&all->pipe[i]) > 1)
			exec_pipe_process(all, goodpath, args);
		else
			exec_last_pipe_process(all, goodpath, args);
		del_array(&args);
		ft_strdel(&goodpath);
		//printf("<%s>\n", all->pipe[i]);
		//printf("%zu\n", ft_tablen(&all->pipe[i]));
		i++; 
	}
	}
	else
		wait(NULL);
	//exit(1);
	//write(0, "\n", 1);
	//write(1, "finish\n", 7);
}

void	exec_pipe_process(t_all *all, char *cmd, char **args)
{
	pid_t	child;
	int		fds[2];

	pipe(fds);
//	printf("|%s|\n", args[0]);
//	printf("|%s|\n", args[1]);	
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

void	exec_last_pipe_process(t_all *all, char *cmd, char **args)
{
	pid_t	child;
	//int		statut;

	if (cmd == NULL)
		return ;
	if ((child = fork()) == -1)
		write(1, "fork  error\n", 11);
	if (child == 0)
	{
		if (execve(cmd, args, all->dupenv) == -1)
			write(1, "execve error\n", 13);
	}
	else
		wait(NULL);
}