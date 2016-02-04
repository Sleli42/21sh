/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:12:44 by skhatir           #+#    #+#             */
/*   Updated: 2016/01/29 10:34:49 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			var_len(char *var)
{
	int		i;

	i = 1;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	return (i - 1);
}

char		*replace_lv(char *var, t_cmd **cmd_t, int index, t_var *local_var)
{
	int		len;
	char	*var_fo;
	t_var	*nav;

	(void)index;
	nav = local_var;
	len = var_len(var);
	var_fo = ft_strsub(var, 1, len);
	(void)cmd_t;
	while (nav)
	{
		if (!ft_strcmp(var_fo, nav->var_name))
			return (nav->content);
		nav = nav->next;
	}
	if (!nav)
		return (var);
	return (NULL);
}


void		find_lv(t_all *all, int lv)
{
	char	p[all->cmd_termcaps->lenght];
	char	*p2;
	t_cmd	*nav;
	char	*new_s;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;
	int		ct;

	i = 0;
	new_s = NULL;
	tmp = NULL;
	tmp2 = NULL;
	(void)lv;
	ft_memset(p, 0, all->cmd_termcaps->lenght);
	nav = all->cmd_termcaps->head;
	while (nav)
	{
		p[i++] = nav->c;
		nav = nav->next;
	}
	p[i] = 0;
	p2 = p;
	i = 0;
	nav = all->cmd_termcaps->head;
	while (p2[i] && nav)
	{
		ct = 1;
		if (p2[i++] == '$')
		{
			i--;
			tmp = i ? ft_strsub(p2, 0, i) : NULL;
			tmp2 = ft_strdup(replace_lv(&p2[i], &nav, i, all->local_var));
			i += tmp ? ft_strlen(tmp) : 0;
			tmp3 = ft_strjoin(tmp, tmp2);
			tmp ? ft_strdel(&tmp) : NULL;
			tmp = ft_strjoin(new_s, tmp3);
			tmp3 ? ft_strdel(&tmp3) : NULL;
			tmp2 ? ft_strdel(&tmp2) : NULL;
			new_s ? ft_strdel(&new_s) : NULL;
			new_s = ft_strdup(tmp);
			tmp ? ft_strdel(&tmp) : NULL;
			p2 += i ? i : var_len(p2) + 1;
			ct += var_len(p2);
			i = 0;
		}
		while (ct-- && nav)
			nav = nav->next;
	}
	if (i)
	{
		tmp = new_s ? ft_strdup(new_s) : NULL;
		new_s ? ft_strdel(&new_s) : NULL;
		new_s = ft_strjoin(tmp, p2);
	}
	realloc_termcaps_cmd(all, new_s);
}
