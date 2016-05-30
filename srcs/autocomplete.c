/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:48:16 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:10:37 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	add_spaces(t_all *all, int tmp_len, int ct)
{
	if (tmp_len < all->maxlen_arg \
				&& ct != all->files_by_row - 1)
	{
		write(1, " ", 1);
		while (tmp_len++ < all->maxlen_arg)
			write(1, " ", 1);
	}
}

char	*cut_equ(char *s)
{
	char	*ret;
	int		i;
	int		ct;

	i = ft_strlen(s) - 1;
	ct = 0;
	while (s[i])
	{
		if (s[i] == '/')
			break ;
		i--;
	}
	i += 1;
	ret = ft_strnew((int)ft_strlen(s) - i);
	while (s[i])
		ret[ct++] = s[i++];
	ret[ct] = '\0';
	return (ret);
}

char	*cut_dir(char *s)
{
	int		ct;
	int		i;
	char	*ret;

	i = (int)ft_strlen(s) - 1;
	ct = 0;
	while (s[i])
	{
		if (s[i] == '/')
			break ;
		i--;
	}
	ret = ft_strnew(i + 1);
	while (ct <= i)
	{
		ret[ct] = s[ct];
		ct++;
	}
	ret[ct] = '\0';
	return (ret);
}

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
		(nav->next) ? add_spaces(all, tmp_len, ct) : NULL;
		nav = nav->next;
		ct++;
	}
}

void	search_autocomplete(t_all *all)
{
	// printf("pos: %d && save pos: %d\n", CURSOR, all->save_curs);
	all->save_curs = CURSOR;
	// printf("CURSOR : %d\n", CURSOR);
	create_cmd(all);
	// printf("CURSOR : %d\n", CURSOR);
	// CURSOR = all->save_curs;
	if (all->cmd[0] == 0 || (ft_strlen(all->cmd) >= 1 \
				&& no_spaces(all->cmd_termcaps->head) && all->cmd[0] != '/'))
		search_bin_path(all);
	else if (all->cmd[CURSOR - PROMPT_LEN - 1] == ' ')
		open_path_directory(all, "./");
	else if (all->cmd[0] == '/' && all->cmd[ft_strlen(all->cmd) - 1] == '/')
		open_path_directory(all, cut_dir(all->cmd));
	else
	{
		cut_cmd_equ(all);
		list_dir_equ(all);
	}
}
