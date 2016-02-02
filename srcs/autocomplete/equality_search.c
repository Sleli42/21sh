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

int		is_dir(t_all *all, char *s)
{
	char		*tmp;
	struct stat lol;

	if (all->tmp_dir)
		tmp = ft_strjoin(all->tmp_dir, s);
	else
		tmp = ft_strdup(s);
	if (stat(tmp, &lol) == -1)
		return (-1);
	ft_strdel(&tmp);
	// printf("mode: %d\n", lol.st_mode);
	// if (all->tmp_dir)
	// 	printf("tmp_dir: |%s|\n", all->tmp_dir);
	// printf("test s : |%s|\n", s);
	if (S_ISDIR(lol.st_mode))
		return (1);
	if (S_ISREG(lol.st_mode))
		return (0);
	return (0);
}

char	*update_tmp_cmd(t_all *all, char *str2add, int len2skip)
{
	char	*tmp;
	int		ct;
	int		i;
	int		save;

	ct = 0;
	i = 0;
	// printf("all->cmd: %s\n", all->cmd);
	// printf("\nint: %d\n", (CURSOR - PROMPT_LEN) - len2skip);
	str2add = (is_dir(all, str2add)) ? ft_strjoin(str2add, "/") : str2add;
	all->replace_cursor = CURSOR + (int)ft_strlen(str2add) - 1;
	tmp = ft_strnew(ft_strlen(all->cmd) - len2skip + ft_strlen(str2add) + 1);
	while (all->cmd[i])
	{
		if (ct == (CURSOR - PROMPT_LEN) - len2skip)
			break ;
		// ft_putstr("TURN\n");
		tmp[ct++] = all->cmd[i++];
		// printf("all->Cmd[ct]: [ %c ]\n", all->cmd[ct]);
		// printf("tmp[ct]: [ %c ]\n", tmp[ct]);
	}
	// printf("tmp: |%s|\n", tmp);
	save = i + len2skip;
	i = 0;
	while (str2add[i])
		tmp[ct++] = str2add[i++];
	// printf("all->cmd[c]: |%c|\n", all->cmd[save]);
	while (all->cmd[save])
		tmp[ct++] = all->cmd[save++];
	tmp[ct] = 0;
	// printf("tmp: |%s|\n", tmp);
	// printf("str2add: |%s|\n", str2add);
	all->already_open = 1;
	return (tmp);
}

char	*open_right_directory(t_all *all, char *equ2find)
{
	stat(equ2find, &all->stat);
	// printf("equ2find: |%s|\n", equ2find);
	if (equ2find[ft_strlen(equ2find) - 1] == '/' && S_ISDIR(all->stat.st_mode))
	{
		// ft_putstr("DIRECTORY\n");
		return (equ2find);
	}
	else
	{
		if (all->already_open)
		{
			// printf("dir: %s", all->tmp_dir);
			return (all->tmp_dir);
		}
		else
			return ("./");
	}
	return (NULL);
}

void	list_dir_equ(t_all *all, char *equ2find)
{
	DIR			*entry;
	t_dirent	*dirp;
	char		*dir2open;

	all->list_dir = create_clst();
	all->tmp_cmd = ft_strdup(all->cmd);
	dir2open = open_right_directory(all, equ2find);
	if (equ2find[ft_strlen(equ2find) - 1] == '/')
	{
		// ft_putstr("HERE\n");
		if (all->tmp_dir)
			ft_strdel(&all->tmp_dir);
		all->tmp_dir = ft_strdup(equ2find);
		all->already_open = 1;
		all->replace_cursor = CURSOR + 1;
		open_path_directory(all, equ2find);
	}
	else
	{
		// printf("dir2open : |%s|\n", dir2open);
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
		{
			all->tmp_cmd = update_tmp_cmd(all, all->list_dir->head->arg,
				(int)ft_strlen(equ2find));
		}
		else if (all->list_dir->lenght > 1)
			display_elems(all, all->list_dir);
		else
		{
			tputs_termcap("bl");
			return ;
		}
	}
	all->already_autocomplete = 1;
	loop(all);
}