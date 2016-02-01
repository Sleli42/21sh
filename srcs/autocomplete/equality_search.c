/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 00:48:53 by lubaujar          #+#    #+#             */
/*   Updated: 2016/02/01 00:48:55 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	list_dir_equ(t_all *all, char *dir2open, char *equ2find)
{
	DIR			*entry;
	t_dirent	*dirp;

	all->list_dir = create_clst();
	all->tmp_cmd = ft_strdup(all->cmd);
	//printf("tmpcmd: |%s|\n", all->tmp_cmd);
	if (!dir2open)
		dir2open = ft_strdup("./");
	// if (dir2open[ft_strlen(dir2open) - 1] == '/')
	// 	dir2open[ft_strlen(dir2open) - 1] = '\0';
	// printf("dir2open : |%s|\n", dir2open);
	// printf("equ2find : |%s|\n", equ2find);
	if (!(entry = opendir(dir2open)))
		error("OPENDIR");
	while ((dirp = readdir(entry)))
	{
		if (!ft_strncmp(dirp->d_name, equ2find, ft_strlen(equ2find)))
			clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
	}
	closedir(entry);
	//printf("all->tmp_cmd :|%s|\n", all->tmp_cmd);
	//all->tmp_cmd  = update_tmp_cmd(all->cmd);
	//printf("all->tmp_cmd :|%s|\n", all->tmp_cmd);
	if (all->list_dir->lenght > 100)
	{
		char	buff[1];
		printf("display %d possibilities ? y or n\n", (int)all->list_dir->lenght);
		read(0, buff, 1);
		if (*buff == 'y')
			display_elems(all, all->list_dir);
	}
	if (all->list_dir->lenght == 1)
	{
		all->tmp_cmd = update_tmp_cmd(all, all->list_dir->head->arg);
		//printf("all->cmd: |%s|\n", all->cmd);
		//printf("all_>tmpcmd: |%s|\n", all->tmp_cmd);
	}
	loop(all);
}