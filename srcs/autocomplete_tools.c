/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 00:55:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:10:32 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	ask_for_big_display(t_all *all)
{
	char	buff[1];

	ft_putstr("display ");
	ft_putnbr((int)all->list_dir->lenght);
	ft_putstr(" possibilities ? y or n\n");
	read(0, buff, 1);
	if (*buff == 'y')
	{
		sort_name(&all->list_dir->head);
		display_elems(all, all->list_dir);
	}
	else if (*buff == 'n')
		return ;
}

int		check_prev_directory(char *s)
{
	int		ct;

	ct = ft_strlen(s) - 1;
	if (!s)
		return (0);
	while (s[ct])
	{
		if (s[ct] == ' ')
			return (0);
		if (s[ct] == '/' && s[ct - 1] != ' ')
			return (1);
		ct--;
	}
	return (0);
}

void	cut_cmd_equ(t_all *all)
{
	int		ct;
	int		tmp;

	ct = 0;
	tmp = (CURSOR - PROMPT_LEN) - 1;
	all->already_open = check_prev_directory(all->cmd);
	if (all->already_open && all->cmd[tmp] != '/')
		while (all->cmd[tmp] && all->cmd[tmp] != '/')
			tmp--;
	else
		while (all->cmd[tmp] && all->cmd[tmp] != ' ')
			tmp--;
	all->equ2find = ft_strnew((CURSOR - PROMPT_LEN) - tmp);
	tmp += 1;
	while (all->cmd[tmp] && all->cmd[tmp] != ' ')
		all->equ2find[ct++] = all->cmd[tmp++];
	all->equ2find[ct] = '\0';
}
