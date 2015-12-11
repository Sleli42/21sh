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

int		define_nb_files_by_row(t_all *all, t_dlist *lst)
{
	int		ret;

	all->maxlen_arg = find_maxlen_elem(lst);
	ret = 0;
	// printf("largeur: %d\n", all->ws.ws_col);
	// printf("maxlen: %d\n", all->maxlen_arg);
	while (all->ws.ws_col > (all->maxlen_arg + 9))
	{
		all->ws.ws_col -= (all->maxlen_arg + 9);
		ret++;
	}
	// printf("ret = %d\n", ret);
	return (ret);
}

void	display_elems(t_all *all, t_dlist *lst)
{
	t_node	*nav;
	int		ct;
	int		len;

	nav = lst->head_node;
	ct = 0;
	all->files_by_row = define_nb_files_by_row(all, lst);
	while (nav)
	{
		len = ft_strlen(nav->s);
		if (ct == all->files_by_row - 1)
		{
			write(1, "\n", 1);
			ct = 0;
		}
		ft_putstr(nav->s);
		while (len++ < (all->maxlen_arg + 11) && nav->next != NULL)
			write(1, " ", 1);
		ct++;
		nav = nav->next;
	}
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
		if (dirp->d_name[0] != '.')
			clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
	sort_name(&all->list_dir->head_node);
	init_windows_size(all);
	write(1, "\n", 1);
}

void	open_directory(t_all *all)
{
	DIR			*entry;
	char		*dir;

	// if (!all->already_open)
	// {
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
		display_elems(all, all->list_dir);
		all->already_open = 1;
		all->stop = 0;
		if (closedir(entry) == -1)
			error("CLOSEDIR");
		ft_strdel(&dir);
	}
	// else
	// {

	// }
}

