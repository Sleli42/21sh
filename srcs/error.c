/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:32:41 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:32:43 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	error(char *err)
{
	if (ft_strcmp(err, "MALLOC") == 0)
		ft_putendl("Malloc error.");
	return ;
}

void	term_error(char *err)
{
	if (!ft_strcmp(err, "GETENV"))
		ft_putstr("getenv() error\n");
	if (!ft_strcmp(err, "TGETENT"))
		ft_putstr("tgetent() error\n");
	if (!ft_strcmp(err, "TCGETATTR"))
		ft_putstr("tcgetattr() error\n");
	if (!ft_strcmp(err, "TCSETATTR"))
		ft_putstr("TCSETATTR() error\n");
}