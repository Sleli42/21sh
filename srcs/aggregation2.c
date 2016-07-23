/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:11:09 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:04:07 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	exec_agg2_extended_2(t_all *all, char **split_2exec)
{
	if (all->fd2restore == 1)
	{
		close(STDOUT_FILENO);
		split_2exec = rework_args_2_exec(split_2exec, "1>&-");
	}
	else if (all->fd2restore == 2)
	{
		close(STDERR_FILENO);
		split_2exec = rework_args_2_exec(split_2exec, "2>&-");
	}
	if (all->dbl_fd == -1)
		return ;
	else if (all->dbl_fd)
		split_2exec = rework_args_2_exec(split_2exec,\
						split_2exec[ft_tablen(split_2exec) - 1]);
	exec_right_binary(all, split_2exec);
	if (all->fd2restore >= 1 && all->fd2restore <= 2)
		dup2((all->fd2restore == 1) ? all->dupout
			: all->duperr, all->fd2restore);
}

void	exec_agg2_extended(t_all *all, char **split_agg, char *file)
{
	char	**split_2exec;

	split_2exec = rework_args_2_exec(split_agg, ">&");
	if (!ft_isdigit(file[0]) && file && ft_strcmp(file, "-"))
	{
		if ((all->fd2open = open(file, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
		dup2(all->fd2open, 1);
		dup2(all->fd2open, 2);
		close(all->fd2open);
		exec_right_binary(all, split_2exec);
		dup2(all->dupout, 1);
		dup2(all->duperr, 2);
	}
	else
		exec_agg2_extended_2(all, split_agg);
}

void	exec_agg2(t_all *all, char *cmd)
{
	char	**split_agg;

	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	if (len_array(split_agg) > 1 && split_agg[0][0] == '>')
		split_agg = replace_argv(split_agg, ">&");
	if (!check_error(all, split_agg, ">&"))
		return ;
	else if (check_close_fd(split_agg))
		close_fd(all, split_agg[ft_tablen(split_agg) - 1]);
	else if (check_fd_to_fd(split_agg[ft_tablen(split_agg) - 1]))
		exec_double_fd(all, split_agg);
	all->dupout = dup(1);
	all->duperr = dup(2);
	exec_agg2_extended(all, split_agg, \
			split_agg[len_array(split_agg) - 1]);
	(split_agg && *split_agg) ? del_array(&split_agg) : NULL;
}
