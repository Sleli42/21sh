/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:23:54 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:23 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

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
		if ((!redirect[0][0]) || len_array(redirect) < 2)
			return (redirection_error_2());
		redirect[1] = ft_epur_str(redirect[1]);
		if ((all->fd2open = open(redirect[1], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		{
			redirection_error(redirect[1]);
			return ;
		}
		argv = ft_strsplit(redirect[0], ' ');
		dupstdout = dup(1);
		dup_and_exec(all, argv, dupstdout, 1);
		redirect ? del_array(&redirect) : NULL;
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
	printf("len: %d\n", len_array(redirect));
	if ((!redirect[0][0]) || len_array(redirect) < 3)
		return (redirection_error_2());
	redirect[1] = ft_epur_str(redirect[1 + 1]);
	if ((all->fd2open = open(redirect[1], \
				O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	{
		redirection_error(redirect[1]);
		return ;
	}
	argv = ft_strsplit(redirect[0], ' ');
	dupstdout = dup(1);
	dup_and_exec(all, argv, dupstdout, 1);
	redirect ? del_array(&redirect) : NULL;
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
		/**
		*** BUG ex: "wc < srcs/lol.c > file"
		*** no such file "srcs... > file"
		**/
		if ((!redirect[0][0]) || len_array(redirect) < 2)
			return (redirection_error_2());
		redirect[1] = ft_epur_str(redirect[1]);
		if ((all->fd2open = open(redirect[1], O_RDONLY)) == -1)
		{
			redirection_error(redirect[1]);
			return ;
		}
		argv = ft_strsplit(redirect[0], ' ');
		dupstdin = dup(0);
		dup_and_exec(all, argv, dupstdin, 0);
		redirect ? del_array(&redirect) : NULL;
	}
}

void	read_stdin(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	char	*tmp_buff;

	argv = NULL;
	redirect = NULL;
	redirect = ft_strsplit(cmd, '<');
	argv = ft_strsplit(redirect[0], ' ');
	if ((!redirect[0][0]) || len_array(redirect) < 3)
		return (redirection_error_2());
	while (1)
	{
		ft_putstr("> ");
		tmp_buff = read_stdin_cpy_buff();
		if (read_stdin_cmp_key(all, argv,
				ft_epur_str(redirect[1 + 1]), tmp_buff))
			break ;
		write(1, "\n", 1);
	}
	redirect ? del_array(&redirect) : NULL;
}
