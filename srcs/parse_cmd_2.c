/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:31:40 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 14:31:41 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			count_medium_split(char *s)
{
	int		ct;
	int		ret;

	ct = 0;
	ret = 0;
	while (s && s[ct])
	{
		if ((s[ct] == '&' && s[ct + 1] == '&')
			|| (s[ct] == '|' && s[ct + 1] == '|'))
			ret++;
		ct++;
	}
	return (ret + (ret + 1));
}

void		medium_split_extend(char **medium, char *tmp, int *i)
{
	if (ft_strlen(tmp) > 0 && !(ft_strlen(tmp) == 1 && tmp[0] == 32))
	{
		medium[*i] = ft_epur_str(tmp);
		*i = *i + 1;
	}
	ft_bzero(tmp, 150);
}

void		medium_split_extend_2(char **medium, char *cmd, int *i, int *ct)
{
	char	*temp;
	int		h;

	temp = ft_strnew(50);
	h = 0;
	while (cmd[*ct])
	{
		if (cmd[*ct] == ' ')
			break ;
		temp[h++] = cmd[(*ct)++];
	}
	temp[h] = 0;
	medium[*i] = ft_strdup(temp);
	*i = *i + 1;
	ft_strdel(&temp);
}
