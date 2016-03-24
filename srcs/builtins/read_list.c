/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 13:19:49 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:08:17 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define NV nav->var_name && var_cp->var_name

static void		update_content(t_var *nav, t_var *var_cp)
{
	nav->content ? ft_strdel(&nav->content) : NULL;
	nav->content = ft_strdup(var_cp->content);
	var_cp->content ? ft_strdel(&var_cp->content) : NULL;
	var_cp->var_name ? ft_strdel(&var_cp->var_name) : NULL;
}

static void		add_back(t_var *var_cp, t_var **local_var)
{
	t_var		*nav;
	t_var		*cpy;

	cpy = init_caps();
	cpy->var_name = ft_strdup(var_cp->var_name);
	cpy->content = ft_strdup(var_cp->content);
	nav = (*local_var) ? (*local_var) : NULL;
	if (!nav)
		(*local_var) = cpy;
	else
	{
		while (nav)
		{
			if (NV && !ft_strcmp(nav->var_name, var_cp->var_name))
				return (update_content(nav, var_cp));
			else if (!nav->next)
			{
				nav->next = cpy;
				cpy->prev = nav;
				return ;
			}
			nav = nav->next;
		}
	}
}

void			creat_var(t_all *all, char *var, char *in)
{
	t_var		*var_cp;

	var_cp = NULL;
	if (*var == '$')
		var++;
	if ((var_cp = (t_var *)malloc(sizeof(t_var *))) == NULL)
		exit(printf("MALLOC LOCAL VAR FAIL\n"));
	var_cp->var_name = ft_strdup(var);
	var_cp->content = ft_strdup(in);
	if (ft_strlen(var_cp->var_name) > all->max_len)
		all->max_len = ft_strlen(var_cp->var_name);
	add_back(var_cp, &all->local_var);
	var_cp ? free(var_cp) : NULL;
	var_cp = NULL;
}
