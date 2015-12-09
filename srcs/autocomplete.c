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

char	*find_path(char *cmd)
{
	char	*path;
	int		ct;
	int		i;

	ct = ft_strlen(cmd) - 1;
	i = 0;
	if (!(path = (char *)malloc(sizeof(char *))))
		error("MALLOC");
	while (cmd[ct] != ' ')
		ct--;
	while (cmd[ct++])
		path[i++] = cmd[ct];
	path[i] = 0;
	if (path[0] == 0 && ft_strlen(cmd) > 1)
		path = ft_strdup(".");
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	return (path);
}

char	*search_equ(char *dir)
{
	t_dirent	*dirp;
	DIR			*entry;
	char		*tofind;
	int			ct;

	ct = -1;
	if (!(tofind = (char *)malloc(sizeof(char) * ft_strlen(dir))))
		error("MALLOC");
	while (++ct < (int)ft_strlen(dir) - 1)
		tofind[ct] = dir[ct];
	tofind[++ct] = 0;
	if (!(entry = opendir("./")))
		error("OPENDIR");
	while ((dirp = readdir(entry)) != NULL)
	{
		if (ft_strncmp(tofind, dirp->d_name, ft_strlen(tofind)) == 0)
			return (ft_strdup(dirp->d_name));
	}
	if (closedir(entry) == -1)
		error("CLOSEDIR");
	return (NULL);
}

// void	display_elems(t_dlist *list)
// {
// 	t_node	*nav = list->head_node;
// 	int		i = 0;

// 	while (nav)
// 	{
// 		if (i % 3)
// 			printf("\n");
// 		ft_putstr(nav->s);
// 		ft_putchar('\t');
// 		i++;
// 		nav = nav->next;
// 	}
// }

void	list_elems(t_all *all, DIR *entry)
{
	t_dirent	*dirp;

	all->list_dir = create_dlst();
	while ((dirp = readdir(entry)))
		dlst_add_back(all->list_dir, dlst_node_new(dirp->d_name, all->list_dir->lenght));
	display_elems(all->list_dir);
	/***
					go to ft_select . . .
	***/
}

void	open_directory(t_all *all)
{
	DIR			*entry;
	char		*dir;

	create_cmd(all);
	dir = find_path(all->cmd);
	if (!(entry = opendir(dir)))
	{
		if ((dir = search_equ(dir)) == NULL)
		{
			write(1, "\n", 1);
			loop(all);
		}
		else
		{
			add_missing_char_to_cmd(all, dir);
			entry = opendir(dir);
		}
	}
	list_elems(all, entry);
	// while ((dirp = readdir(entry)) != NULL)
	// {
	// 	printf("%s\n", dirp->d_name);
	// }
	if (closedir(entry) == -1)
		error("CLOSEDIR");
	ft_strdel(&dir);
}

