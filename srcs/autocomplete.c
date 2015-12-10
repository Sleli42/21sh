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
/*
void	sort_name(t_all **alst)
{s
	t_all	*tmp;
	int		i;

	tmp = *alst;
	i = 0;
	if (tmp)
	{
		while (i++ < len_lst(tmp))
		{
			while (tmp->next)
			{
				if (ft_strcmp(tmp->content->name, tmp->next->content->name) > 0)
					swap_elem(&tmp, &tmp->next);
				tmp = tmp->next;
			}
			tmp = *alst;
		}
	}
}

void	swap_elem(t_all **a, t_all **b)
{
	t_infos	*temp;

	temp = (*a)->content;
	(*a)->content = (*b)->content;
	(*b)->content = temp;
}
*/

void	swap_elems(t_node *a, t_node *b)
{
	char	*tmp_s;
	int		tmp_i;

	tmp_s = ft_strdup(a->s);
	tmp_i = a->index;
	ft_strdel(&a->s);
	a->s = ft_strdup(b->s);
	a->index = b->index;
	ft_strdel(&b->s);
	b->s = ft_strdup(tmp_s);
	ft_strdel(&tmp_s);
	b->index = tmp_i;
}

void	sort_name(t_node **lst)
{
	t_node			*nav;
	int				i;

	nav = *lst;
	i = len_lst_node(*lst);
	if (nav)
	{
		while (i--)
		{
			nav = *lst;
			while (nav && nav->next)
			{
				if (ft_strcmp(nav->s, nav->next->s) > 0)
					swap_elems(nav, nav->next);
				nav = nav->next;
			}
		}
	}
}

void	display_elems(t_dlist *list)
{

	/*
			A REFAIRE AVEC WINSIZE */
	// t_node	*nav;
	// int		i = 0;
	// // int		ct = 4;
	// int		maxlen = find_maxlen_elem(list);

	// nav = list->head_node;
	// write(1, "\n", 1);
	// while (nav)
	// {
	// 	if (nav->s[0] != '.')
	// 	{
	// 		i = ft_strlen(nav->s);
	// 		ft_putstr(nav->s);
	// 		while (i < maxlen)
	// 		{
	// 			write(1, " ", 1);
	// 			i++;
	// 		}
	// 	}
	// 	nav = nav->next;
	// }
}

void	display_dlst(t_dlist *lst)
{
	t_node	*nav = lst->head_node;

	while (nav)
	{
		printf("%s\n", nav->s);
		nav = nav->next;
	}
}

void	list_elems(t_all *all, DIR *entry)
{
	t_dirent	*dirp;

	all->list_dir = create_dlst();
	while ((dirp = readdir(entry)))
	{
		if (dirp->d_name[0] != '.')
			dlst_add_back(all->list_dir,
				dlst_node_new(dirp->d_name, all->list_dir->lenght));
	}
	display_elems(all->list_dir);
	write(1, "\n", 1);
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
	all->stop = 0;
	// while ((dirp = readdir(entry)) != NULL)
	// {
	// 	printf("%s\n", dirp->d_name);
	// }
	if (closedir(entry) == -1)
		error("CLOSEDIR");
	ft_strdel(&dir);
}

