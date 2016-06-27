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
		cmd = formatting_redirect_cmd(cmd, ">");
		redirect = ft_strsplit(cmd, ' ');
		if (len_array(redirect) > 1 && redirect[0][0] == '>')
			redirect = replace_argv(redirect, ">");
		if (!check_error(all, redirect, ">"))
			return ;
		argv = rework_args_2_exec(redirect, ">");
		if ((all->fd2open = open(redirect[len_array(redirect) - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return (redirection_error(redirect[len_array(redirect) - 1]));
		dupstdout = dup(1);
		(!all->err) ? dup_and_exec(all, argv, dupstdout, 1) : NULL;
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
	cmd = formatting_redirect_cmd(cmd, ">>");
	redirect = ft_strsplit(cmd, ' ');
	if (len_array(redirect) > 1 && redirect[0][0] == '>')
		redirect = replace_argv(redirect, ">>");
	if (!check_error(all, redirect, ">>"))
		return ;
	argv = rework_args_2_exec(redirect, ">>");
	if ((all->fd2open = open(redirect[len_array(redirect) - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return (redirection_error(redirect[len_array(redirect) - 1]));
	dupstdout = dup(1);
	(!all->err) ? dup_and_exec(all, argv, dupstdout, 1) : NULL;
	redirect ? del_array(&redirect) : NULL;
}

void	read_file(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		cmd = formatting_redirect_cmd(cmd, "<");
		redirect = ft_strsplit(cmd, ' ');
		if (len_array(redirect) > 1 && redirect[0][0] == '<')
			redirect = replace_argv(redirect, "<");
		if (!check_error(all, redirect, "<"))
			return ;
		if (check_double_redirection(redirect))
			return (exec_double_redirection(all, redirect));
		argv = rework_args_2_exec(redirect, "<");
		if ((all->fd2open = open(redirect[len_array(redirect) - 1], \
			O_RDONLY, 0644)) == -1)
			return (redirection_error(redirect[len_array(redirect) - 1]));
		all->dupstdin = dup(0);
		(!all->err) ? dup_and_exec(all, argv, all->dupstdin, 0) : NULL;
		redirect ? del_array(&redirect) : NULL;
	}
}

void	read_stdin_loop(t_all *all, char **argv, char **redirect)
{
	char	*tmp_buff;

	tmp_buff = NULL;
	while (1)
	{
		ft_putstr("> ");
		tmp_buff = read_stdin_cpy_buff();
		if (ft_strcmp(tmp_buff, redirect[len_array(redirect) - 1]))
		{
			ft_putstr_fd(tmp_buff, all->fd2open);
			ft_putstr_fd("\n", all->fd2open);
		}
		if (read_stdin_cmp_key(all, argv, \
			redirect[len_array(redirect) - 1], tmp_buff))
			break ;
		write(1, "\n", 1);
	}
}

void	read_stdin(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;

	cmd = formatting_redirect_cmd(cmd, "<<");
	redirect = ft_strsplit(cmd, ' ');
	if (len_array(redirect) > 1 && redirect[0][0] == '<')
		redirect = replace_argv(redirect, "<<");
	if (!check_error(all, redirect, "<<"))
		return ;
	if (len_array(redirect) < 3)
		return ;
	argv = NULL;
	if ((all->fd2open = open(".tmp_file", \
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		error("OPEN");
	argv = rework_args_2_exec(redirect, "<<");
	read_stdin_loop(all, argv, redirect);
	redirect ? del_array(&redirect) : NULL;
}
