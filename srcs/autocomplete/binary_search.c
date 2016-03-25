/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 00:47:56 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:10:27 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	results_analysis_bin(t_all *all)
{
	if (all->list_dir->lenght <= 0)
	{
		tputs_termcap("bl");
		return ;
	}
	else if (all->list_dir->lenght == 1)
	{
		if (all->tmp_cmd)
			ft_strdel(&all->tmp_cmd);
		all->tmp_cmd = ft_strdup(ft_strjoin(all->list_dir->head->arg, " "));
	}
	else if (all->list_dir->lenght > 100)
		ask_for_big_display(all);
	else
	{
		sort_name(&all->list_dir->head);
		display_elems(all, all->list_dir);
	}
}

void	search_bin_path_loop(t_all *all)
{
	char		*tmp;
	DIR			*entry;
	t_dirent	*dirp;
	int			ct;

	ct = 0;
	while (all->path2exec[ct])
	{
		tmp = ft_strjoin(all->path2exec[ct++], "/");
		if (!(entry = opendir(tmp)))
			return ;
		else
		{
			while ((dirp = readdir(entry)))
			{
				if (!ft_strncmp(dirp->d_name, all->cmd, \
						ft_strlen(all->cmd)))
					clst_add_elem_back(all->list_dir, \
						clst_create_elem(dirp->d_name));
			}
			closedir(entry);
		}
		ft_strdel(&tmp);
	}
}

void	search_bin_path(t_all *all)
{
	all->tmp_cmd = ft_strdup(all->cmd);
	all->list_dir = create_clst();
	search_bin_path_loop(all);
	results_analysis_bin(all);
	del_clist(&all->list_dir);
	all->already_autocomplete = 1;
	loop(all);
}
