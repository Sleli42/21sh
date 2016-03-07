/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:11:09 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/07 13:11:10 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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

int		check_error_agg2(t_all *all, char **split, char *file)
{
	while (split && ft_strcmp(*split, ">&"))
		split++;
	if (!ft_strcmp(*(split + 1), "-"))
		close_fd(all, *(split - 1));
	else if (ft_isdigit(file[0]) && ft_atoi(file) > 2)
	{
		ft_putstr("sh: ");
		ft_putnbr(ft_atoi(file));
		ft_putstr(": Bad file descriptor\n");
		return (1);
	}
	else if ((ft_isdigit(*(split - 1)[0]) && ft_atoi(*(split - 1)) > 2
		&& ft_strcmp(file, "-")) || !ft_isdigit(*(split + 1)[0]))
	{
		ft_putstr("sh: ");
		ft_putstr(file);
		ft_putstr(": ambiguous redirect\n");
		return (1);
	}
	return (0);
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

void	exec_agg2(t_all *all, char *cmd)
{
	char	**split_agg;
	char	**split_2exec;
	char	*file;
	int		dupout;
	int		duperr;
	// int		tmp_fd;

	split_2exec = NULL;
	file = NULL;
	cmd = rework_cmd_agg2(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	file = get_good_file_agg2(split_agg);
	dupout = dup(1);
	duperr = dup(2);
	// display_array(split_agg);
	// printf("file fnd: |%s|\n", file);
	if (!check_error_agg2(all, split_agg, file))
	{
		split_2exec = create_argv_cmd_agg2(split_agg, file);
		// display_array(split_2exec);
		if (!ft_isdigit(file[0]) && ft_strcmp(file, "-"))
		{
			if ((all->fd2open = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
				write(1, "err0r1\n", 6);
			dup2(all->fd2open, 1);
			dup2(all->fd2open, 2);
			close(all->fd2open);
			exec_right_binary(all, split_2exec);
			dup2(dupout, 1);
			dup2(duperr, 2);
		}
		else
		{
			exec_right_binary(all, split_2exec);
			if (all->fd2restore >= 1 && all->fd2restore <= 2)
			{
				// choose_good_dup(all);
				dup2((all->fd2restore == 1) ? dupout : duperr, all->fd2restore);
				all->fd2restore = -1;
			}
		}
		(split_2exec) ? del_array(&split_2exec) : NULL;
	}
	(split_agg) ? del_array(&split_agg) : NULL;
}