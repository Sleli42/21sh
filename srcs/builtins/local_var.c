/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:12:44 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:08:58 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define F2 fbox.p2 && *fbox.p2

char		*search_env_var(char *var, t_all *all)
{
	t_node	*nav;
	char	**envp;

	nav = all->env->head;
	if (!(envp = (char **)malloc(sizeof(char *) * all->env->tail->index + 2)))
		return (NULL);
	envp[all->env->tail->index + 1] = 0x0;
	while (nav)
	{
		envp[nav->index] = nav->s;
		nav = nav->next;
	}
	while (envp && *envp)
	{
		if (!ft_strncmp(var, *envp, ft_strlen(var)))
			return (var_env(*envp));
		envp++;
	}
	return (NULL);
}

char		*replace_lv(char *var, t_cmd **cmd_t, int index, t_all *all)
{
	int		len;
	char	*var_fo;
	t_var	*nav;
	char	*ret;

	(void)index;
	nav = all->local_var;
	if ((len = var_len(var)) < 0)
		len = 1;
	var_fo = ft_strsub(var, 1, len);
	if (!ft_strcmp(var_fo, "$") || !ft_strcmp(var_fo, "!"))
		return (*var_fo == '$' ? ft_itoa(getpid()) : "0");
	if ((ret = search_env_var(var_fo, all)))
		return (ret);
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

int			stock_true_var(t_flv *fbox, int i, t_all *all)
{
	int		tmp;

	tmp = 0;
	fbox->tmp = i ? ft_strsub(fbox->p2, 0, i) : NULL;
	fbox->tmp2 = ft_strdup(replace_lv(&fbox->p2[i], &fbox->nav, i, all));
	tmp = var_len(&fbox->p2[i]);
	i += tmp > 0 ? tmp : 1;
	fbox->tmp3 = ft_strjoin(fbox->tmp, fbox->tmp2);
	fbox->tmp ? ft_strdel(&fbox->tmp) : NULL;
	fbox->tmp = ft_strjoin(fbox->new_s, fbox->tmp3);
	fbox->new_s ? ft_strdel(&fbox->new_s) : NULL;
	fbox->new_s = ft_strdup(fbox->tmp);
	fbox->tmp3 ? ft_strdel(&fbox->tmp3) : NULL;
	fbox->tmp2 ? ft_strdel(&fbox->tmp2) : NULL;
	fbox->tmp ? ft_strdel(&fbox->tmp) : NULL;
	fbox->p2 += i ? i + 1 : var_len(fbox->p2);
	return (0);
}

void		find_lv(t_all *all)
{
	int		i;
	char	p[all->cmd_termcaps->lenght];
	t_flv	fbox;

	i = 0;
	init_fbox(&fbox, all, p);
	while (fbox.nav)
	{
		p[i++] = fbox.nav->c;
		fbox.nav = fbox.nav->next;
	}
	p[i] = 0;
	fbox.p2 = p;
	i = 0;
	fbox.nav = all->cmd_termcaps->head;
	while (fbox.p2[i] && fbox.nav)
		i = fbox.p2[i] == '$' ? stock_true_var(&fbox, i, all) : (i + 1);
	if (i)
	{
		fbox.tmp = fbox.new_s ? ft_strdup(fbox.new_s) : NULL;
		fbox.new_s ? ft_strdel(&fbox.new_s) : NULL;
		fbox.new_s = ft_strjoin(fbox.tmp, F2 ? fbox.p2 : NULL);
		fbox.tmp ? ft_strdel(&fbox.tmp) : NULL;
	}
	realloc_termcaps_cmd(all, fbox.new_s);
}
