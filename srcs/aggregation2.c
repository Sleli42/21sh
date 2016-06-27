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

void	exec_agg2_extended(t_all *all, char **split_agg, char *file)
{
	char	**split_2exec;

	split_2exec = rework_args_2_exec(split_agg, ">&");
	if (!ft_isdigit(file[0]) && ft_strcmp(file, "-"))
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
	{
		exec_right_binary(all, split_2exec);
		if (all->fd2restore >= 1 && all->fd2restore <= 2)
			dup2((all->fd2restore == 1) ? all->dupout
				: all->duperr, all->fd2restore);
	}
}

void	exec_agg2(t_all *all, char *cmd)
{
	char	**split_agg;

	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	if (len_array(split_agg) > 1 && split_agg[0][0] == '>')
		split_agg = replace_argv(split_agg, ">&");
	if (!check_error(all, split_agg, ">&"))
		return ;
	all->dupout = dup(1);
	all->duperr = dup(2);
	exec_agg2_extended(all, split_agg, \
			split_agg[len_array(split_agg) - 1]);
	(split_agg) ? del_array(&split_agg) : NULL;
}
