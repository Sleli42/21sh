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

	init_windows_size(all);
	all->maxlen_arg = find_maxlen_elem(lst);
	ret = 0;
	// printf("largeur: %d\n", all->ws.ws_col);
	// printf("maxlen: %d\n", all->maxlen_arg);
	while (all->ws.ws_col > (all->maxlen_arg + 5))
	{
		all->ws.ws_col -= (all->maxlen_arg + 5);
		ret++;
	}
	// printf("ret = %d\n", ret);
	return (ret);
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
/*
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
*/
void	display_elems(t_all *all, t_clist *lst)
{
	t_select	*nav;
	int			ct;
	int			tmp_len;

	nav = lst->head;
	ct = 0;
	all->files_by_row = define_nb_files_by_row(all, lst);
	write(1, "\n", 1);
	while (nav && ct < all->files_by_row)
	{
		tmp_len = ft_strlen(nav->arg) - 1;
		if (ct == all->files_by_row - 1)
		{
			ct = 0;
			write(1, "\n", 1);
		}
		ft_putstr(nav->arg);
		if (tmp_len < all->maxlen_arg && nav->next)
		{
			write(1, " ", 1);
			while (tmp_len++ < all->maxlen_arg + 5)
				write(1, " ", 1);
		}
		nav = nav->next;
		ct++;
	}
	write(1, "\n", 1);
	//printf("nb files by rows: %d\n", all->files_by_row);
}

int		no_spaces(t_cmd *lst)
{
	t_cmd	*tmp = lst;

	if (tmp->c == '.' && tmp->next->c == '/')
		return (0);
	while (tmp)
	{
		if (tmp->c == ' ')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

// void	display_current(t_all *all, t_select *nav)
// {

// }

char	*cut_cmd(char *cmd)
{
	int 	ct = ft_strlen(cmd) - 1;
	int		i = 0;
	char	*ret;

	ret = (char *)malloc(sizeof(char *));
	while (cmd[ct] != ' ')
		ct--;
	ct--;;
	while (cmd[ct] != ' ')
	{
		if (ct == 0)
			break ;
		ct--;
	}
	while (cmd[ct] != ' ')
		ret[i++] = cmd[ct++];
	ret[i++] = ' ';
	ret[i] = 0;
	return (ret);
}
/*
void	search_equ(t_all *all, char *dir)
{
	t_dirent	*dirp;
	DIR			*entry;
	char		*tofind;

	if (!dir)
		return ;
	all->list_dir = create_clst();
	//all->tmp_cmd = ft_strdup(dir);
//	printf("dir |%s|\n", dir);
	if (dir[0] != '.')
	{
		all->tmp_cmd = cut_cmd(all->cmd);
	}
	else
	{
		if (dir[0] == '.' && dir[1] == '/')
			all->tmp_cmd = ft_strdup("./");
		else
			all->tmp_cmd = ft_strdup(dir);
			if (!all->hidden_file || ft_strlen(all->cmd) > 2)
				dir = dir + 2;
		//printf("dir |%s|\n", dir);
	}
	if (!(tofind = (char *)malloc(sizeof(char) * ft_strlen(dir))))
		error("MALLOC");

	tofind = ft_strdup(dir);
	//printf("tofind : %s\n", tofind);
	//printf("|%c|\n", tofind[ft_strlen(tofind) - 1]);
	if (tofind[ft_strlen(tofind) - 1] == '.')
		all->hidden_file = 1;
	else
		all->hidden_file = 0;
	if (!(entry = opendir("./")))
		error("OPENDIR");
	while ((dirp = readdir(entry)) != NULL)
	{
		if (!ft_strncmp(tofind, dirp->d_name, ft_strlen(tofind)))
			clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
	}
	if (closedir(entry) == -1)
		error("CLOSEDIR");
	ft_strdel(&tofind);
	display_elems(all, all->list_dir);
	all->already_autocomplete = 1;
	all->already_equ = 1;
	loop(all);
}
*/
char	*find_path(char *s)
{
	int		ct;
	int		i;
	char	*ret;

	ct = ft_strlen(s) - 1;
	i = 0;
	while (s[ct] != ' ')
		ct--;
	ret = (char *)malloc(sizeof(char*));
	while (s[ct++])
		ret[i++] = s[ct];
	ret[i] = 0;
	return (ret);
}

char	*cut_dir_path(char *s)
{
	char	*ret;
	int		ct;
	int		i;

	//printf("s fct: %s\n", s);
	if (!(ret = (char*)malloc(sizeof(char *))))
		return (NULL);
	ct = ft_strlen(s) - 1;
	i = 0;
//	printf("-> |%c|\n", s[ct]);
	if (s[ct] != '/')
	{
		while (s[ct])
		{
			ct--;
			if (s[ct] == 47)
				break ;
		}
	}
	//printf("s[ct] : |%c|\n", s[ct]);
	if (s[ct] == '/')
	{
		while (s[ct])
		{
			ct--;
			if (s[ct] == 32)
				break ;
		}
	}
	ct++;
//	printf("-> |%c|\n", s[ct]);
	while (s[ct] && s[ct - 1] != '/')
		ret[i++] = s[ct++];
	ret[i] = 0;
	//printf("ret: |%s|\n", ret);
	return (ret);
}

char	*cut_equ_path(char *s)
{
	char	*ret;
	int		ct;
	int		i;

	ct = ft_strlen(s) - 1;
	i = 0;
	if (!(ret = (char *)malloc(sizeof(char*))))
		return (NULL);
	while (s[ct])
	{
		if (s[ct] == 47)
			break;
		ct--;
	}
	ct++;
	while (s[ct])
		ret[i++] = s[ct++];
	ret[i] = 0;
	return (ret);
}

/**
***		autocomplete bad dir -> segfault **
**/


void	search_path_directory(t_all *all, char *dir2open)
{
	t_dirent	*dirp;
	DIR			*entry;

	all->list_dir = create_clst();
	if (!(entry = opendir(dir2open)))
		error("OPENDIR");
	while ((dirp = readdir(entry)))
		clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
	sort_name(&all->list_dir->head);
	display_elems(all, all->list_dir);
	closedir(entry);
	all->tmp_dir = ft_strdup(dir2open);
	all->already_equ = 1;
	loop(all);
}

char	*update_tmp_cmd(char *s)
{
	int 	ct;
	int		i;
	char	*ret;

	ct = ft_strlen(s) - 1;
	i = 0;
	if (!(ret = (char *)malloc(sizeof(char *))))
		return (NULL);
	while (s[ct])
	{
		if (s[ct] == 47)
			break;
		ct--;
	}
	ct++;
	while (i < ct)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	printf("ret: %s\n", ret);
	return (ret);
}

void	list_dir_equ(t_all *all, char *dir2open, char *equ2find)
{
	DIR			*entry;
	t_dirent	*dirp;

	all->list_dir = create_clst();
	if (!(entry = opendir(dir2open)))
		error("OPENDIR");
	while ((dirp = readdir(entry)))
	{
		if (!ft_strncmp(dirp->d_name, equ2find, ft_strlen(equ2find)))
			clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
	}
	closedir(entry);
	all->tmp_cmd  = update_tmp_cmd(all->cmd);
	display_elems(all, all->list_dir);
	loop(all);
}

void	search_bin_path(t_all *all)
{
	int			ct;
	char		*tmp;
	DIR			*entry;
	t_dirent	*dirp;

	ct = 0;
	//printf("[autocomplete] cmd: %s\n", all->cmd);
	all->tmp_cmd = ft_strdup(all->cmd);
	all->list_dir = create_clst();
	while (all->path2exec[ct])
	{
		tmp = ft_strjoin(all->path2exec[ct++], "/");
		if (!(entry = opendir(tmp)))
			error("OPENDIR");
		while ((dirp = readdir(entry)))
			if (!ft_strncmp(dirp->d_name, all->cmd, ft_strlen(all->cmd)))
				clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
		closedir(entry);
		ft_strdel(&tmp);
	}
	if (all->list_dir->lenght == 1)
	{
		ft_strdel(&all->tmp_cmd);
		all->tmp_cmd = ft_strdup(all->list_dir->head->arg);
	}
	display_elems(all, all->list_dir);
	all->already_autocomplete = 1;
	loop(all);
}

void	open_current_dir(t_all *all)
{
	DIR			*entry;
	t_dirent	*dirp;

	// tmp_path = ft_strdup("./");
	//printf("tmpPath: %s\n", tmp_path);
	all->tmp_cmd = ft_strdup(all->cmd);
	// tmp = cut_cmd(all->cmd);
	all->list_dir = create_clst();
	if (!(entry = opendir("./")))
		error("OPENDIR");
	while ((dirp = readdir(entry)))
		//if (dirp->d_name[0] != '.')
			clst_add_elem_back(all->list_dir, clst_create_elem(dirp->d_name));
	sort_name(&all->list_dir->head);
	display_elems(all, all->list_dir);
	closedir(entry);
	all->already_autocomplete = 1;
	loop(all);
}

void	open_directories(t_all *all)
{
	create_cmd(all);
	//printf("|%c|\n", all->cmd[ft_strlen(all->cmd) - 1]);
	if (ft_strlen(all->cmd) >= 1 && no_spaces(all->cmd_termcaps->head))
		search_bin_path(all);
	else if (all->cmd[ft_strlen(all->cmd) - 1] == ' ')
		open_current_dir(all);
	else
		NULL;
/*	else if (all->cmd[ft_strlen(all->cmd) - 1] == '/')
		open_current_path(all);
	else
		search_equ(all);*/
}

/*
void	open_directories(t_all *all)
{
	// DIR		*entry;
	// char	*dir;

	// dir = NULL;
	create_cmd(all);
	//printf("cursor: %d\n", all->cursor_pos);
	//printf("all->cmd : %s\n", all->cmd);
	if (all->cmd[0] == '.' && !all->cmd[1] && !all->hidden_file)
	{
		ft_strdel(&all->cmd);
		all->cmd = ft_strdup("./");
	}
	//printf("cmd : %s\n", all->cmd);
	if (all->cmd[ft_strlen(all->cmd) - 1] == '/')
	{
		//printf("all->cmd : %s\n", all->cmd);
		search_path_directory(all, cut_dir_path(all->cmd));
		// if (all->already_autocomplete)
		// 	printf("already_autocomplete\n");
		// if (all->already_equ)
		// 	printf("already_equ\n");

	}
	else if (all->already_equ)
	{
		list_dir_equ(all, cut_dir_path(all->cmd), cut_equ_path(all->cmd));
	}
	else if (goto_elem(all->cmd_termcaps->head, all->cursor_pos - 1) != ' ')
	{
		if (all->cmd[0] == '.')
		{
			//printf("|%c|\n", all->cmd[2]);
			if (all->already_autocomplete && ft_strlen(all->cmd) > 2)
			{
				search_equ(all, all->cmd);
			}
			else
				search_current_dir(all);
		}
		else if (no_spaces(all->cmd_termcaps->head))
			search_bin_path(all);
		else
			search_equ(all, find_path(all->cmd));
	}
	else{
		write(1, "prob\n", 5);
		search_current_dir(all);
	}
}
*/