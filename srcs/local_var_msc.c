/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_msc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 10:32:00 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:08:52 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void		init_fbox(t_flv *fbox, t_all *all, char *p)
{
	fbox->new_s = NULL;
	fbox->tmp = NULL;
	fbox->tmp2 = NULL;
	ft_memset(p, 0, all->cmd_termcaps->lenght);
	fbox->nav = all->cmd_termcaps->head;
	fbox->env_var = all->dupenv ? all->dupenv : NULL;
}

int			is_array_lv(char a)
{
	if (a == '{' || a == '}' || a == '[' || a == ']' || a == '@')
		return (0x1);
	return (0x0);
}

int			var_len(char *var)
{
	int		i;

	i = 1;
	if (!var[i])
		return (0);
	if (var[i] == '$' || var[i] == '$')
		return ((var[i] == '$' ? CURENT_PID : LAST_PID));
	while (var[i] && (ft_isalnum(var[i]) || is_array_lv(var[i])))
		i++;
	return (i - 1);
}

char		*var_env(char *target)
{
	char	*dup;

	dup = NULL;
	while (target && *target && *target != '=')
		target++;
	if (!target || !*target || *target != '=')
		return (NULL);
	return ((dup = ft_strdup(++target)));
}
