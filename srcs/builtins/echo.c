/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 16:48:20 by skhatir           #+#    #+#             */
/*   Updated: 2016/01/31 19:23:25 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		built_echo(t_all *all, char *cmd)
{
	int		i;
	char	n;

	(void)all;
	i = 4;
	n = 0;
	if (cmd[++i])
	{
		i += cmd[i] == '-' ? 1 : 0;
		cmd[i]== 'n' ? n++ : i--;
	}
	if (i < 4)
		return (ft_putendl("echo usage: echo [-n] [var]"));
	while (cmd[i])
	{
		ft_putchar(cmd[i++]);
		cmd[i++] == '\n' && n ? ft_putchar(cmd[i++]) : NULL;
	}
}
