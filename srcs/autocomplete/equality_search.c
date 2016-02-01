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

char	*update_tmp_cmd(t_all *all, char *str2add)
{
	printf("all->cmd: |%s|\n", all->cmd);
	printf("str2add: |%s|\n", str2add);
	return (NULL);
}

void	list_dir_equ(t_all *all, char *equ2find)
{
	DIR			*entry;
	t_dirent	*dirp;
	char		*dir2open;

	all->list_dir = create_clst();
	all->tmp_cmd = ft_strdup(all->cmd);
	dir2open = (equ2find[ft_strlen(equ2find) - 1] == '/')
		? ft_strdup(equ2find) : ft_strdup("./");
	if (equ2find[ft_strlen(equ2find) - 1] == '/')
		open_path_directory(all, equ2find);
	else
	{
		if (!(entry = opendir(dir2open)))
			;
		else
		{
			while ((dirp = readdir(entry)))
			{
				if (!ft_strncmp(dirp->d_name, equ2find, ft_strlen(equ2find)))
					clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
			}
			closedir(entry);
		}
		if (all->list_dir->lenght == 1)
			all->tmp_cmd = update_tmp_cmd(all, all->list_dir->head->arg);
		else if (all->list_dir->lenght > 1)
			display_elems(all, all->list_dir);
		else
			tputs_termcap("bl");
	}
	all->already_autocomplete = 1;
	loop(all);
}