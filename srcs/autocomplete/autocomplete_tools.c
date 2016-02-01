/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 00:55:58 by lubaujar          #+#    #+#             */
/*   Updated: 2016/02/01 00:55:59 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		find_maxlen_elem(t_clist *lst)
{
	t_select	*nav = lst->head;
	int			ret = 0;

	ret = ft_strlen(nav->arg);
	while (nav->next)
	{
		//ret = ft_strlen(nav->arg);
		if (ft_strlen(nav->arg) > (size_t)ret)
			ret = ft_strlen(nav->arg);
		nav = nav->next;
	}
	return (ret);
}

int		define_nb_files_by_row(t_all *all, t_clist *lst)
{
	int		ret;

	init_windows_size(all);
	all->maxlen_arg = find_maxlen_elem(lst);
	ret = 0;
	// printf("largeur: %d\n", LINE_LEN);
	// printf("maxlen: %d\n", all->maxlen_arg);
	while (LINE_LEN > (all->maxlen_arg + 2))
	{
		LINE_LEN -= (all->maxlen_arg + 2);
		// printf("largeur: %d\n", LINE_LEN);
		ret++;
	}
	// printf("ret = %d\n", ret);
	// exit(1);
	return (ret);
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

char	*cut_cmd_equ(char *s)
{
	int		ct;
	int		i;
	char	*ret;

	ct = ft_strlen(s) - 1;
	i = 0;
	ret = (char *)malloc(sizeof(char *));
	if (s[ct] == '/')
		ct--;
	while (s[ct] != ' ')
		ct--;
	ct++;
	while (s[ct])
		ret[i++] = s[ct++];
	ret[i] = 0;
	return (ret);
}

char	*update_tmp_cmd(t_all *all, char *str2add)
{
	int		ct;
	int 	i;

	(void)str2add;
	ct = ft_strlen(all->tmp_cmd) - 1;
	i = 0;
	while (all->tmp_cmd[ct] != ' ')
		ct--;
	// printf("-> |%s|\n", all->tmp_cmd);
	// printf("-> |%s|\n", str2add);
	return (NULL);
}