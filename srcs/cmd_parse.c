/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:12:29 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/04 17:12:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	parse_command(t_all *all, char *buff)
{
	int		i;

	i = -1;
	all->parsecmd = NULL;
	if (buff[0] != '\0')
		all->parsecmd = ft_strsplit(buff, ';');
	if (all->parsecmd != NULL)
		while (all->parsecmd[++i])
			all->parsecmd[i] = ft_epur_str(all->parsecmd[i]);
}

int		check_redirection(char *s)
{
	if (s && *s)
	{
		while (*s)
		{
			if (*s == '>' || *s == '<' || *s == '|'
				|| (*s == '>' && (*s + 1) == '>')
				|| (*s == '<' && (*s + 1) == '<'))
				return (1);
			s++;
		}
	}
	return (0);
}