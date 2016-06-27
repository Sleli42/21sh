/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:46:12 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/27 12:46:14 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	**replace_argv(char **array, char *redir)
{
	char	**ret;
	int	ct;
	int	ct2;

	ct = 0;
	ct2 = 1;
	if (!array || !(ret = (char **)malloc(sizeof(char *) * \
		len_array(array) + 1)))
		return (NULL);
	while (array[ct2])
	{
		if (!ft_strcmp(array[ct2 - 1], redir))
			break ;
		ct2++;
	}
	ct2 += 1;
	while (array[ct2])
		ret[ct++] = ft_strdup(array[ct2++]);
	ct2 = 0;
	while (array[ct2] && ct < len_array(array))
		ret[ct++] = ft_strdup(array[ct2++]);
	ret[ct] = NULL;
	return (ret);
}

int		count_args(char **array, char *redir)
{
	int		ret;
	int		ct;

	ret = 0;
	ct = 0;
	while (array[ct])
	{
		if (!ft_strcmp(array[ct], redir))
			break ;
		ct++;
		ret++;
	}
	return (ret);
}

char	**rework_args_2_exec(char **array, char *redir)
{
	int		ct;
	int		stop;
	char	**ret;

	ct = 0;
	stop = count_args(array, redir);
	if (!(ret = (char **)malloc(sizeof(char *) * stop + 1)))
		return (NULL);
	while (array[ct] && ct < stop)
	{
		ret[ct] = ft_strdup(array[ct]);
		ct++;
	}
	ret[ct] = NULL;
	return (ret);
}

char	*formatting_redirect_cmd(char *cmd, char *redir)
{
	int		ct;
	int		ct2;
	char	*ret;

	ct = 0;
	ct2 = 0;
	ret = ft_strnew(ft_strlen(cmd) + 20);
	while (cmd[ct])
	{
		if (cmd[ct] == redir[0] && cmd[ct + 1] != ' ' && cmd[ct + 1] != redir[0])
		{
			ret[ct2++] = cmd[ct++];
			ret[ct2++] = ' ';
		}
		else
			ret[ct2++] = cmd[ct++];
	}
	ret[ct2] = 0;
	ft_strdel(&cmd);
	return (ret);
}

int		check_if_valid_cmd(t_all *all, char *try)
{
	int		ct;
	char	*bin_tmp;

	ct = 0;
	bin_tmp = NULL;
	while (all->path2exec[ct])
	{
		if (!(bin_tmp = create_path(all->path2exec[ct], try)))
		{
			write_error_exec(try);
			return (0);
		}
		if (bin_tmp && good_access(bin_tmp))
			break ;
		bin_tmp ? ft_strdel(&bin_tmp) : NULL;
		ct++;
	}
	if (!all->path2exec[ct])
	{
		all->err = 1;
		write_error(try);
		return (0);
	}
	return (1);
}
