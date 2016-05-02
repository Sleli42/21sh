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

char	*rework_cmd_agg2(char *cmd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_strnew(ft_strlen(cmd) + 20);
	if (ret && cmd)
	{
		while (cmd[i])
		{
			if ((cmd[i] == '>' && cmd[i - 1] != ' ')
				|| (cmd[i - 1] == '&' && cmd[i] != ' '))
				ret[j++] = ' ';
			ret[j++] = cmd[i++];
		}
		ret[j] = '\0';
	}
	return (ret);
}

char	*get_good_file_agg2(char **array)
{
	while (array && *array)
	{
		if (!ft_strcmp(*array, ">&"))
			return (*(array + 1));
		array++;
	}
	return (NULL);
}

char	**create_argv_cmd_agg2(char **split_agg, char *file)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * \
					count_arg_agg(split_agg, file) + 1)))
		error("MALLOC");
	while (split_agg && *split_agg)
	{
		if (*(split_agg + 1) && ft_isdigit(*split_agg[0]) \
								&& !ft_strcmp(*(split_agg + 1), ">&"))
			split_agg++;
		if (*(split_agg + 1) && ft_isdigit(*split_agg[0]) \
								&& !ft_strcmp(*(split_agg - 1), ">&"))
			split_agg++;
		if (ft_strcmp(*split_agg, ">&") && ft_strcmp(*split_agg, file))
			ret[i++] = ft_strdup(*split_agg);
		split_agg++;
	}
	ret[i] = NULL;
	return (ret);
}

void	exec_agg2_extended(t_all *all, char **split_agg, char *file)
{
	char	**split_2exec;

	split_2exec = create_argv_cmd_agg2(split_agg, file);
	if (!ft_isdigit(file[0]) && ft_strcmp(file, "-"))
	{
		if ((all->fd2open = open(file, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			write(1, "err0r1\n", 6);
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
	(split_2exec && *split_2exec) ? del_array(&split_2exec) : NULL;
}

void	exec_agg2(t_all *all, char *cmd)
{
	char	**split_agg;
	char	*file;

	file = NULL;
	cmd = rework_cmd_agg2(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	file = get_good_file_agg2(split_agg);
	all->dupout = dup(1);
	all->duperr = dup(2);
	if (!check_error_agg2(all, split_agg, file))
		exec_agg2_extended(all, split_agg, file);
	(split_agg) ? del_array(&split_agg) : NULL;
}
