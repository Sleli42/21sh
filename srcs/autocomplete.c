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

void	open_and_read_dir(t_all *all)
{
	t_dirent	*dirp;
	DIR			*entry;

	if (!(entry = opendir()))
}

/*
t_all	*open_directory(t_opt *opt, char *dir_name)
{
	t_all		*list;
	t_dirent	*dirp;
	DIR			*entry;
	char		*path;

	list = NULL;
	if (!(entry = opendir(dir_name)))
		err();
	while ((dirp = readdir(entry)) != NULL)
	{
		path = ft_strjoin(dir_name, dirp->d_name);
		list_elem(&list, opt, dirp->d_name, path);
		ft_strdel(&path);
	}
	if (closedir(entry) == -1)
		err();
	return (list);
}
*/

