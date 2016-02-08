/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:48:16 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/09 14:48:22 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	display_elems(t_all *all, t_clist *lst)
{
	t_select	*nav;
	int			ct;
	int			tmp_len;

	nav = lst->head;
	ct = 0;
	all->files_by_row = define_nb_files_by_row(all, lst);
	write(1, "\n", 1);
	while (nav)
	{
		tmp_len = ft_strlen(nav->arg) - 1;
		if (ct == all->files_by_row)
		{
			ct = 0;
			write(1, "\n", 1);
		}
		ft_putstr(nav->arg);
		if (tmp_len < all->maxlen_arg && nav->next \
							&& ct != all->files_by_row - 1)
		{
			write(1, " ", 1);
			while (tmp_len++ < all->maxlen_arg)
				write(1, " ", 1);
		}
		nav = nav->next;
		ct++;
	}
}

void	search_autocomplete(t_all *all)
{
	create_cmd(all);
	if (all->cmd[0] == 0 || (ft_strlen(all->cmd) >= 1 \
							&& no_spaces(all->cmd_termcaps->head)))
		search_bin_path(all);
	else if (all->cmd[CURSOR - PROMPT_LEN - 1] == ' ')
		open_path_directory(all, "./");
	else
		list_dir_equ(all, cut_cmd_equ(all));
}