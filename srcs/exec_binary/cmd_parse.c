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

void	parse_command(t_all *all, char *buff)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	all->parsecmd ? del_array(&all->parsecmd) : NULL;
	all->parsecmd = NULL;
	if (buff && buff[0] != '\0')
	{
		all->parsecmd = ft_strsplit(buff, ';');
		if (!all->parsecmd || !*all->parsecmd || !ft_isprint(**all->parsecmd))
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

int		check_redirection(char *s)
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
