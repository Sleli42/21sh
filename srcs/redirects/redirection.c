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

void	dup_and_exec(t_all *all, char **argv, int fd2back, int fd2dup)
{
	dup2(all->fd2open, fd2dup);
	close(all->fd2open);
	exec_right_binary(all, argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
	del_array(&argv);
}

void	erase_and_replace(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	redirect = ft_strsplit(cmd, '>');
	redirect[1] = ft_epur_str(redirect[1]);
	if ((all->fd2open = open(redirect[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		write(1, "err0r1\n", 6);//shell_error("OPEN", redirect[1]);
	argv = ft_strsplit(redirect[0], ' ');
	dupstdout = dup(1);
	dup_and_exec(all, argv, dupstdout, 1);
	del_array(&redirect);
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
	redirect = ft_strsplit(cmd, '<');
	redirect[1] = ft_epur_str(redirect[1]);
	if ((all->fd2open = open(redirect[1], O_RDONLY)) == -1)
		write(1, "err0r\n", 6);//shell_error("OPEN", redirect[1]);
	argv = ft_strsplit(redirect[0], ' ');
	dupstdin = dup(0);
	dup_and_exec(all, argv, dupstdin, 0);
	del_array(&redirect);
}

void	read_stdin(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	char	*key;
	char	*buff;
	int		dupstdin;

	(void)all;
	argv = NULL;
	buff = NULL;
	redirect = ft_strsplit(cmd, '<');
	key = ft_epur_str(redirect[1 + 1]);
	argv = ft_strsplit(redirect[0], ' ');
	while (1)
	{
		ft_putstr("heredoc> ");
		get_next_line(0, &buff);
		if (ft_strcmp(key, buff) == 0)
		{
			dupstdin = dup(0);
			dup_and_exec(all, argv, dupstdin, 0);
			break ;
		}
		else
			if (buff != NULL)
				ft_strdel(&buff);
	}
	del_array(&redirect);
}