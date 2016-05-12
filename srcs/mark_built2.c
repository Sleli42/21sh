/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_built2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 15:20:56 by skhatir           #+#    #+#             */
/*   Updated: 2016/05/12 19:54:59 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char			*obtain_history_p(char *history)
{
	char		*ret;

	if (!history || *history)
	{
		printf("-v\n");
		return (NULL);
	}
	printf("[%s]\n", history);
	return ((ret = *history && *history == ':' ? ++history : obtain_history_p(++history)));
}

int				get_arg(char *p_cmd)
{
	int			ret;

	ret = 0;
	while (*p_cmd)
	{
		if (*p_cmd++ == ' ')
			ret++;
		if (*p_cmd && ret && ft_isascii(*p_cmd) && *p_cmd != ' ')
			ret++;
	}
	return (ret);
}

char			*first_cmd(char *cmd)
{
	char		*format;
	int			i;

	i = 0;
	format = NULL;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return ((format = ft_strsub(cmd, 0, i)));
}

int				get_index(char *p_cmd)
{
	int			ret;
	char		*format;

	ret = 0;
	while (ft_isdigit(p_cmd[ret]))
		ret++;
	format = ft_strsub(p_cmd, 0, ret);
	ret = ft_atoi(format);
	ft_strdel(&format);
	return (ret - 1);
}

void			join_params(char **p_cmd, char *orig_cmd)
{
	char		*format;

	format = NULL;
	while (*orig_cmd && *orig_cmd != ' ')
		orig_cmd++;
	format = ft_strjoin((*p_cmd), orig_cmd);
	ft_strdel(p_cmd);
	(*p_cmd) = format;
}
