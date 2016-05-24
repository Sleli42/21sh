/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 09:27:43 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/09 09:27:44 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char		**medium_split(char **medium, char *cmd)
{
	int		ct;
	int		i;
	int		j;
	char	*tmp;

	ct = 0;
	i = 0;
	j = 0;
	tmp = ft_strnew(150);
	while (cmd[ct])
	{
		if ((cmd[ct] == '&' && cmd[ct + 1] == '&')
			|| (cmd[ct] == '|' && cmd[ct + 1] == '|'))
		{
			medium_split_extend(medium, tmp, &i);
			medium_split_extend_2(medium, cmd, &i, &ct);
			j = 0;
		}
		tmp[j++] = cmd[ct++];
	}
	tmp[j] = 0;
	if (ft_strlen(tmp) > 0 && !(ft_strlen(tmp) == 1 && tmp[0] == 32))
		medium[i++] = ft_epur_str(tmp);
	medium[i] = NULL;
	return (medium);
}

char		**medium_parse(char *cmd)
{
	int		temp;
	char	**medium;

	temp = count_medium_split(cmd);
	if (!(medium = (char **)malloc(sizeof(char *) * temp + 1)))
		error("MALLOC");
	medium = medium_split(medium, cmd);
	return (medium);
}

void		parse_command(t_all *all, char *buff)
{
	int		ct;
	char	**big_parse;

	ct = 0;
	big_parse = ft_strsplit(buff, ';');
	if (!(all->parsecmd = (char ***)malloc(sizeof(char **) * \
										len_array(big_parse) + 1)))
		error("MALLOC");
	while (big_parse[ct])
	{
		big_parse[ct] = ft_epur_str(big_parse[ct]);
		all->parsecmd[ct] = medium_parse(big_parse[ct]);
		ct++;
	}
	all->parsecmd[ct] = NULL;
}

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
