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

char	*open_right_directory(t_all *all, char *equ2find)
{
	stat(equ2find, &all->stat);
	if (equ2find[ft_strlen(equ2find) - 1] == '/' && S_ISDIR(all->stat.st_mode))
		return (equ2find);
	else
	{
		if (all->already_open)
			return (all->tmp_dir);
		else
		{
			if (directory_in_path(all, equ2find))
			{
				all->equ2find = equ2find + all->skip;
				return (cut_directory_in_path(equ2find));
			}
			else
				return ("./");
		}
	}
	return (NULL);
}

void	search_equality(t_all *all, char *equ2find, char *dir2open)
{
	DIR			*entry;
	t_dirent	*dirp;

	if (!(entry = opendir(dir2open)))
		;
	else
	{
		while ((dirp = readdir(entry)))
		{
			if (!ft_strncmp(dirp->d_name, equ2find, ft_strlen(equ2find)))
				clst_add_elem_back(all->list_dir, \
					clst_create_elem(dirp->d_name));
		}
		closedir(entry);
	}
}

void	results_analysis_equ(t_all *all, char *equ2find)
{
	if (all->list_dir->lenght <= 0)
	{
		tputs_termcap("bl");
		return ;
	}
	else if (all->list_dir->lenght == 1)
	{
		all->tmp_cmd = update_tmp_cmd(all, all->list_dir->head->arg,
			(int)ft_strlen(equ2find));
	}
	else if (all->list_dir->lenght > 1)
		display_elems(all, all->list_dir);
}

void	list_dir_equ(t_all *all)
{
	char		*dir2open;

	all->list_dir = create_clst();
	all->tmp_cmd = ft_strdup(all->cmd);
	dir2open = open_right_directory(all, all->equ2find);
	if (EQU_IS_DIRECTORY)
	{
		if (all->tmp_dir)
			ft_strdel(&all->tmp_dir);
		all->tmp_dir = ft_strdup(all->equ2find);
		all->already_open = 1;
		all->replace_cursor = CURSOR + 1;
		open_path_directory(all, all->equ2find);
	}
	else
	{
		search_equality(all, all->equ2find, dir2open);
		results_analysis_equ(all, all->equ2find);
		del_clist(&all->list_dir);
	}
	all->already_autocomplete = 1;
	loop(all);
}
