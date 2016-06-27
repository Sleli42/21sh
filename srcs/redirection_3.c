/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:46:19 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/27 12:46:20 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		check_error(t_all *all, char **array, char *redir)
{
	char	**tmp;
	int		ct;

	ct = 0;
	tmp = array;
	if ((len_array(array) == 1) || (array[1][0] == '&' && !array[1][1]))
		return (redirection_error_2());
	else if (!ft_strcmp(tmp[0], redir) && len_array(array) == 2)
		return (redirection_error_4());
	if (!check_if_valid_cmd(all, tmp[0]))
		return (-1);
	while (tmp[ct])
	{
		if (!ft_strcmp(tmp[ct], redir))
		{
			if (!tmp[ct + 1])
				return (redirection_error_2());
			else if (ct == 0)
				return (redirection_error_4());
		}
		ct++;
	}
	return (1);
}

int		check_double_redirection(char **array)
{
	char	**tmp;
	int		ct;
	int		stop;

	tmp = array;
	ct = 0;
	stop = 0;
	while (tmp[ct])
	{
		if ((tmp[ct][0] == '<' && !stop)
			|| (tmp[ct][0] == '>' && !stop))
			stop += 1;
		else if ((tmp[ct][0] == '>' && stop)
			|| (tmp[ct][0] == '<' && stop))
			stop += 1;
		ct++;
	}
	if (stop == 2)
		return (1);
	return (0);
}

char	*first_redirect(char **array)
{
	char	**tmp;
	int		ct;

	tmp = array;
	ct = 0;
	while (tmp[ct])
	{
		if (tmp[ct][0] == '>' || tmp[ct][0] == '<')
			return (tmp[ct]);
		ct++;
	}
	return (NULL);
}

char	*get_fd_2_open(char **array, char *redir)
{
	char	**tmp;
	int		ct;

	tmp = array;
	ct = 0;
	while (tmp[ct])
	{
		if (tmp[ct][0] == redir[0])
			return (tmp[ct + 1]);
		ct++;
	}
	return (NULL);
}

int		count_redirect(char *s)
{
	int		ct;
	int		ret;

	ct = 0;
	ret = 0;
	if (!s)
		return (0);
	while (s[ct])
	{
		if (s[ct] == '<')
		{
			while (s[ct] == '<')
			{
				ret++;
				if (ret > 2)
					return (ret);
				ct++;
			}
			ret = 0;
		}
		ct++;
	}
	return (ret);
}
