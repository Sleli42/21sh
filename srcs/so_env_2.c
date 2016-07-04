/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_env_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:40:02 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/28 14:40:03 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		env_exec(t_all *all, char **params)
{
	t_env_info		inf;

	init_inf(&inf);
	if (check_params(params, &inf))
		return (1);
	if (inf.exec)
		return (env_bin(all, &inf));
	if (inf.unless != -1 && inf.env_spe)
	{
		set_env_exec(&inf, all);
		return (0);
	}
	if (inf.unless == -1 && inf.env_spe)
	{
		ft_printtab(inf.env_spe);
		return (1);
	}
	return (0);
}

char	**check_format(char *cmd)
{
	char		**ret;

	if (!cmd || !*cmd)
		return (NULL);
	ret = NULL;
	if (!(ret = ft_strsplit(cmd, ' ')))
		return (NULL);
	if (ft_tablen(ret) != 2)
	{
		del_array(&ret);
		ft_putendl("Bad format: set env [var] [content]");
		return (NULL);
	}
	else
		return (ret);
}
