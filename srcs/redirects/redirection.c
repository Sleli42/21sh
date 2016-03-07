/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:23:54 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/04 17:23:55 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
int dup2(int oldfd, int newfd);

dup2() transforme newfd en une copie de oldfd, fermant auparavant newfd
       si besoin est, mais prenez note des points suivants.

       *  Si  oldfd n’est pas un descripteur de fichier valable, alors l’appel
          échoue et newfd n’est pas fermé.

       *  Si oldfd est un descripteur de fichier valable et newfd  a  la  même
          valeur que oldfd, alors dup2() ne fait rien et renvoie newfd.
*/

void	erase_and_replace(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		redirect = ft_strsplit(cmd, '>');
		redirect[1] = ft_epur_str(redirect[1]);
		if ((all->fd2open = open(redirect[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			write(1, "err0r1\n", 6);
		argv = ft_strsplit(redirect[0], ' ');
		dupstdout = dup(1);
		dup_and_exec(all, argv, dupstdout, 1);
		del_array(&redirect);
	}
}

void	add_to_end(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	redirect = ft_strsplit(cmd, '>');
	redirect[1] = ft_epur_str(redirect[1 + 1]);
	if ((all->fd2open = open(redirect[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		write(1, "err0r2\n", 6);//shell_error("OPEN", redirect[1]);
	argv = ft_strsplit(redirect[0], ' ');
	dupstdout = dup(1);
	dup_and_exec(all, argv, dupstdout, 1);
	del_array(&redirect);
}

void	read_file(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdin;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		redirect = ft_strsplit(cmd, '<');
		redirect[1] = ft_epur_str(redirect[1]);
		if ((all->fd2open = open(redirect[1], O_RDONLY)) == -1)
			write(1, "err0r\n", 6);//shell_error("OPEN", redirect[1]);
		argv = ft_strsplit(redirect[0], ' ');
		dupstdin = dup(0);
		dup_and_exec(all, argv, dupstdin, 0);
		del_array(&redirect);
	}
}

void	read_stdin(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	char	*key;
	char	*buff;
	char	*tmp_buff;
	int		dupstdin;
	int		i;

	(void)all;
	argv = NULL;
	buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	tmp_buff = ft_strnew(MAXLEN - 1);
	redirect = ft_strsplit(cmd, '<');
	key = ft_epur_str(redirect[1 + 1]);
	argv = ft_strsplit(redirect[0], ' ');
	while (1)
	{
		i = 0;
		ft_putstr("> ");
		(!buff) ? buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1)): NULL;
		(!tmp_buff) ? tmp_buff = ft_strnew(MAXLEN - 1): NULL;
		while (read(0, buff, (MAXLEN - 1)) != -1)
		{
			if (*buff == '\n')
				break ;
			ft_putchar(*buff);
			tmp_buff[i++] = *buff;
		}
		tmp_buff[i] = '\0';
		if (!ft_strcmp(key, tmp_buff))
		{
			dupstdin = dup(0);
			write(1, "\n", 1);
			dup_and_exec(all, argv, dupstdin, 0);
			break ;
		}
		else
		{
			if (buff && tmp_buff)
			{
				ft_strdel(&buff);
				ft_strdel(&tmp_buff);
			}
		}
		write(1, "\n", 1);
	}
	del_array(&redirect);
}

void	exec_redirect(t_all *all, char *cmd, char **args, char *file, int redir)
{
	pid_t	child;
	int		fd;

	(void)all;
	fd = open_file(file, redir);
	if (cmd == NULL)
		return ;
	if ((child = fork()) == -1)
		write(2, "fork  error\n", 11);
	if (child == 0)
	{
		if (execve(cmd, args, NULL) == -1)
			write(2, "execve error\n", 13);
	}
	else
		wait(NULL);
}