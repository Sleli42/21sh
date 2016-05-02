/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 16:48:20 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:09:04 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		built_echo(t_all *all, char *cmd)
{
	int		i;
	char	n;

	(void)all;
	i = 4;
	n = 0;
	if (cmd[i + 1] && cmd[++i] == '-')
		cmd[++i] == 'n' ? (n++) : (i = (-i + -1));
	if (i < 0)
		return (ft_putendl("echo usage: echo [-n] [var]"));
	i += n - 1;
	while (cmd[++i])
	{
		while (cmd[i] && cmd[i] == '\"')
			i++;
		if (!cmd[i])
			break ;
		ft_putchar(cmd[i]);
	}
	return ((n ? ft_putchar(0) : ft_putchar(10)));
}
