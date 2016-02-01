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
	return (ret - 1);
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

char	*cut_cmd_equ(t_all *all)
{
	int		ct;
	int		tmp;
	char	*ret;

	ct = 0;
	tmp = (CURSOR - PROMPT_LEN) - 1;
	if (!(ret = (char *)malloc(sizeof(char *))))
		error("MALLOC");
	while (all->cmd[tmp] && all->cmd[tmp] != ' ')
		tmp--;
	tmp += 1;
	while (all->cmd[tmp] && all->cmd[tmp] != ' ')
	{
		// printf("tmp: [ %c ]\n", all->cmd[tmp]);
		ret[ct++] = all->cmd[tmp++];
	}
	ret[ct] = '\0';
	// printf("ret: [ %s ]\n", ret);
	return (ret);
}