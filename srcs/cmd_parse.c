/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:12:29 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:24 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			len_array(char **array)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (array[i])
	{
		ret++;
		i++;
	}
	return (ret);
}

void		parse_command(t_all *all, char *buff)
{
	int		i;

	i = 0;
	all->parsecmd ? del_array(&all->parsecmd) : NULL;
	all->parsecmd = NULL;
	if (buff && buff[0] != '\0')
	{
		all->parsecmd = ft_strsplit(buff, ';');
		if (len_array(all->parsecmd) == 1 &&
			(!all->parsecmd || !*all->parsecmd || !ft_isprint(**all->parsecmd)))
			return ;
	}
	else
		return ;
	if (all->parsecmd)
	{
		while (all->parsecmd[i])
		{
			all->parsecmd[i] = ft_epur_str(all->parsecmd[i]);
			i++;
		}
	}
}

int			check_redirection(char *s)
{
	int		ct;

	ct = 0;
	if (s && s[ct])
	{
		while (s[ct])
		{
			if (s[ct] == '>' || s[ct] == '<' || s[ct] == '|' || s[ct] == '&')
				return (1);
			ct++;
		}
	}
	return (0);
}
