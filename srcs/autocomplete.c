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
	// if (path[0] == 0 && ft_strlen(cmd) > 1)
	// 	path = ft_strdup(".");
	// if (path[ft_strlen(path) - 1] != '/')
	// 	path = ft_strjoin(path, "/");
	return (path);
}

char	*search_equ(char *dir)
{
	t_dirent	*dirp;
	DIR			*entry;
	char		*tofind;
	int			ct;

	ct = -1;
	if (!dir)
		return (NULL);
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

void	swap_elems(t_select *a, t_select *b)
{
	char	*tmp_s;
	//int		tmp_i;

	tmp_s = ft_strdup(a->arg);
	//tmp_i = a->index;
	ft_strdel(&a->arg);
	a->arg = ft_strdup(b->arg);
	//a->index = b->index;
	ft_strdel(&b->arg);
	b->arg = ft_strdup(tmp_s);
	ft_strdel(&tmp_s);
	//b->index = tmp_i;
}

void	sort_name(t_select **lst)
{
	t_select		*nav;
	int				i;

	nav = *lst;
	i = len_clst(*lst);
	if (nav)
	{
		while (i--)
		{
			nav = *lst;
			while (nav && nav->next)
			{
				if (ft_strcmp(nav->arg, nav->next->arg) > 0)
					swap_elems(nav, nav->next);
				nav = nav->next;
			}
		}
	}
}

int		define_nb_files_by_row(t_all *all, t_clist *lst)
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

void	display_elems(t_all *all, t_clist *lst)
{
	t_select	*nav;
	int			ct;
	int			len;

	nav = lst->head;
	ct = 0;
	all->files_by_row = define_nb_files_by_row(all, lst);
	while (nav)
	{
		len = ft_strlen(nav->arg);
		if (ct == all->files_by_row - 1)
		{
			write(1, "\n", 1);
			ct = 0;
		}
		//(nav->onArg == 1) ? tputs_termcap("mr") : tputs_termcap("me");
		ft_putstr(nav->arg);
		while (len++ < (all->maxlen_arg + 11))
			write(1, " ", 1);
		ct++;
		nav = nav->next;
	}
	all->nb_char_write = (all->maxlen_arg + 11) * (int)lst->lenght;
}

void	list_elems(t_all *all, DIR *entry)
{
	t_dirent	*dirp;

	all->list_dir = create_clst();
	while ((dirp = readdir(entry)))
	{
		if (dirp->d_name[0] != '.')
		{
			clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
		}
	}
	//sort_name(&all->list_dir->head);
	//init_windows_size(all);
	//write(1, "\n", 1);
}

void	select_arg(t_all *all)
{
	t_select	*nav = all->list_dir->head;
	int			i = -1;

	// write(1, "here\n", 5);
	if (all->ct_select == (int)all->list_dir->lenght)
	{
		all->list_dir->tail->onArg = 0;
		all->ct_select = 0;
	}
	while (++i < all->ct_select)
		nav = nav->next;
	nav->onArg = 1;
	if (nav->prev)
		nav->prev->onArg = 0;
	all->ct_select++;
	// printf("selected arg-> %s\n", nav->arg);
}

void	new_line_autocomplet(t_all *all)
{
	//printf("nbcharwrite: %d\n", all->nb_char_write);
	if (all->nb_char_write > 0)
	{
		while (all->nb_char_write--)
		{
			tputs_termcap("dc");
			tputs_termcap("le");
		}
	}
}

void	display_current(t_all *all, t_select *nav)
{
	ft_putstr(nav->arg);
	all->nb_char_write = ft_strlen(nav->arg);
}

int		no_spaces(t_cmd *lst)
{
	t_cmd	*tmp = lst;

	while (tmp)
	{
		if (tmp->c == ' ')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	open_directory(t_all *all)
{
	// DIR		*entry;
	// char	*dir;

	// dir = NULL;
	if (goto_elem(all->cmd_termcaps->head, all->cursor_pos - 1) != ' ')
	{
		if (no_spaces(all->cmd_termcaps->head))
			search_bin_path();
			//printf("Search path bin\n");
		else
			printf("Search equ\n");
	}
	else
		printf("open './'\n");





	/*
	DIR			*entry;
	char		*dir;
	
	all->stop = 0;
	//tputs_termcap("sc");
	if (!all->already_open)
	{
		//write(1, "\n", 1); ---> to select autocomplete
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
		all->nav_dir = all->list_dir->head;
		//display_elems(all, all->list_dir);
		all->already_open = 1;
		if (closedir(entry) == -1)
			error("CLOSEDIR");
		ft_strdel(&dir);
	}
	else
	{
		new_line_autocomplet(all);
		display_current(all, all->nav_dir);
		all->nav_dir = (all->nav_dir->next) ? all->nav_dir->next : all->list_dir->head;
		//if (all->cmd_termcaps->tail->c == '/')
		//{
		//	add_to_cmd(all, ft_strjoin(all->nav_dir->prev->arg, "/"));
		//	all->already_open = 0;
			//printf("go sous directory autocomplet\n");
		//}
		//simple_display();
		// tputs_termcap("dm");
		// tputs_termcap("cb");
		// tputs_termcap("ed");
		//select_arg(all);
		//display_elems(all, all->list_dir);
		//tputs_termcap("ve");
	}
	*/
}