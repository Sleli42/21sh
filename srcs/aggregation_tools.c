/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:11:28 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:49 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		check_aggregations(char *cmd)
{
	int		ct;

	ct = 0;
	while (cmd[ct] && cmd)
	{
		if ((cmd[ct] == '&' && cmd[ct + 1] == '>')
			|| (cmd[ct] == '>' && cmd[ct + 1] == '&')
			|| (cmd[ct] == '<' && cmd[ct + 1] == '&'))
			return (1);
		ct++;
	}
	return (0);
}

char	*check_file_in_cmd(char *cmd)
{
	while (cmd && *cmd)
	{
		if (*cmd == '>' || *cmd == '<' || *cmd == '&')
			return (NULL);
		cmd++;
	}
	return (cmd);
}

int		count_arg_agg(char **array, char *file)
{
	int		ret;

	ret = 0;
	while (array && *array)
	{
		if ((ft_strcmp(*array, "&>") && ft_strcmp(*array, file))
			|| (ft_strcmp(*array, ">&") && ft_strcmp(*array, file))
			|| (ft_strcmp(*array, "<&") && ft_strcmp(*array, file)))
			ret++;
		array++;
	}
	return (ret);
}

void	close_fd(t_all *all, char *fd2close)
{
	if (ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 0)
		;
	else if ((ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 1)
		|| !ft_isdigit(fd2close[0]))
	{
		all->fd2restore = 1;
		close(STDOUT_FILENO);
	}
	else if ((ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 2))
	{
		all->fd2restore = 2;
		close(STDERR_FILENO);
	}
}

void	exec_aggregations(t_all *all, char *cmd)
{
	char	*tmp;

	tmp = ft_strchr(cmd, '>');
	if (tmp)
	{
		if (*tmp == '>' && *(tmp - 1) == '&')
			exec_agg1(all, cmd);
		else if (*tmp == '>' && *(tmp + 1) == '&')
			exec_agg2(all, cmd);
	}
	else
	{
		tmp = ft_strchr(cmd, '<');
		if (*tmp == '<' && *(tmp + 1) == '&')
			return (ft_putstr("Missing name for redirect.\n"));
	}
}
