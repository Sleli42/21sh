/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality_search_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:06:50 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:10:07 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	*update_tmp_cmd(t_all *all, char *str2add, int len2skip)
{
	char	*tmp;
	int		ct;
	int		i;
	int		save;

	ct = 0;
	i = 0;
	str2add = (is_dir(all, str2add)) ? ft_strjoin(str2add, "/") : str2add;
	all->replace_cursor = CURSOR + (int)ft_strlen(str2add) - 1;
	tmp = ft_strnew(ft_strlen(all->cmd) - len2skip + ft_strlen(str2add) + 1);
	while (all->cmd[i])
	{
		if (ct == (CURSOR - PROMPT_LEN) - len2skip)
			break ;
		tmp[ct++] = all->cmd[i++];
	}
	save = i + len2skip;
	i = 0;
	while (str2add[i])
		tmp[ct++] = str2add[i++];
	while (all->cmd[save])
		tmp[ct++] = all->cmd[save++];
	tmp[ct] = 0;
	all->already_open = 1;
	return (tmp);
}

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
	if (S_ISDIR(lol.st_mode))
		return (1);
	if (S_ISREG(lol.st_mode))
		return (0);
	return (0);
}

int		directory_in_path(t_all *all, char *equ2find)
{
	int		ct;

	if (equ2find[0] == '/')
		return (1);
	ct = CURSOR - PROMPT_LEN;
	while (equ2find[ct--])
	{
		if (equ2find[ct] == '/')
		{
			all->skip = ct + 1;
			return (1);
		}
	}
	return (0);
}

int		check_next_slash(char *s)
{
	int		ct;

	ct = 1;
	if (s)
	{
		while (s[ct])
		{
			if (s[ct] == '/')
				return (1);
			ct++;
		}
	}
	return (0);
}

int		count_nb_dir(char *s)
{
	int		ret;
	int		ct;

	ret = 0;
	ct = 0;
	if (!s)
		return (0);
	while (s[ct])
	{
		if (s[ct] == '/')
			ret++;
		ct++;
	}
	return (ret);
}

char	*cut_directory_in_path(char *equ2find)
{
	int		ct;
	int		i;
	int		count;
	char	*ret;

	// printf("equ: [%s]\n"/, equ2find);
	// if (equ2find[0] == '/')
	// {
	// 	if (!check_next_slash(equ2find))
	// 		return ("/");
	// }
	count = count_nb_dir(equ2find);
	i = 0;
	ct = ft_strlen(equ2find) - 1;
	while (equ2find[ct] && (equ2find[ct] != '/' || equ2find[ct] != ' '))
		ct--;
	ct = 0;
	ret = ft_strnew((ft_strlen(equ2find) - 1) - ct);
	while (equ2find[ct] && count != 0)
	{
		if (equ2find[ct] == '/')
			count--;
		ret[i++] = equ2find[ct++];
		// printf("ret[i]: [%c]\n", ret[i - 1]);
	}
	ret[i] = 0;
	return (ret);
}
