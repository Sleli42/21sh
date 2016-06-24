/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:11:09 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:04:13 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	display_array(char **array)
{
	int	ct;
	char	**tmp;

	tmp = array;
	ct = 0;
	while (tmp[ct])
	{
		ft_putendl(tmp[ct]);
		ct++;
	}
}

char	*get_good_file_agg1(char **array)
{
	while (array && *array)
	{
		if (!ft_strcmp(*array, "&>"))
			return (*(array + 1));
		array++;
	}
	return (NULL);
}

char	**create_argv_cmd_agg1(char **split_agg, char *file)
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
		if (ft_strcmp(*split_agg, "&>") && ft_strcmp(*split_agg, file))
			ret[i++] = ft_strdup(*split_agg);
		split_agg++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*rework_cmd_agg1(char *cmd)
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
			if ((cmd[i] == '&' && cmd[i - 1] != ' ')
				|| (cmd[i - 1] == '>' && cmd[i] != ' ')
				|| (cmd[i - 1] == '<' && cmd[i] != ' '))
				ret[j++] = ' ';
			ret[j++] = cmd[i++];
		}
		ret[j] = '\0';
	}
	return (ret);
}

void	exec_agg1(t_all *all, char *cmd)
{
	char	**split_agg;
	char	**split_2exec;
	char	*file;
	int		dupout;
	int		duperr;

	// ft_putstr("yih\n");
	cmd = rework_cmd_agg1(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	display_array(split_agg);
	file = get_good_file_agg1(split_agg);
	dupout = dup(1);
	duperr = dup(2);
	if ((all->fd2open = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		write(1, "err0r1\n", 6);
	split_2exec = create_argv_cmd_agg1(split_agg, file);
	dup2(all->fd2open, 1);
	dup2(all->fd2open, 2);
	close(all->fd2open);
	exec_right_binary(all, split_2exec);
	dup2(dupout, 1);
	dup2(duperr, 2);
	del_array(&split_agg);
	del_array(&split_2exec);
}
