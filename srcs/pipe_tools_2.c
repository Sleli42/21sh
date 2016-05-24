/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:00:18 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:29 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		check_pipe_error(char ***pipe2exec)
{
	int		ct;

	ct = 0;
	while (pipe2exec[ct])
	{
		if (!len_array(pipe2exec[ct]))
		{
			ft_putstr("zsh: parse error near `|'\n");
			return (0);
		}
		ct++;
	}
	return (1);
}

int		redirect_in_args(char **array)
{
	while (*array)
	{
		if (*array[0] == '>' || *array[0] == '<')
			return (1);
		array++;
	}
	return (0);
}

int		redirect_in_arrays(t_all *all, char ***arrays)
{
	int			count;
	int			ct;

	count = 0;
	while (arrays[count])
	{
		ct = 0;
		while (arrays[count][ct])
		{
			if (arrays[count][ct][0] == '>')
			{
				all->file2redir = ft_strdup(arrays[count][ct + 1]);
				return (1);
			}
			ct++;
		}
		count++;
	}
	return (0);
}
