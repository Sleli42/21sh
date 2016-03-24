/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:15:20 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:08:34 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char					*format_array(char *name, int index, char ck)
{
	char				*tmp;
	char				*tmp2;
	char				*ato;

	tmp = ft_strjoin("${", name);
	ato = ft_itoa(index);
	tmp2 = ft_strjoin("[", ck ? "@" : ato);
	ato ? ft_strdel(&ato) : NULL;
	ato = ft_strjoin(tmp, tmp2);
	tmp ? ft_strdel(&tmp) : NULL;
	tmp2 ? ft_strdel(&tmp2) : NULL;
	tmp2 = ft_strjoin(ato, "]}");
	return (tmp2);
}

char					**do_array(char **cmd_tab, char **var_tab, t_all *all)
{
	int					i;
	int					x;
	char				**ret;

	i = 0;
	(void)cmd_tab;
	while (var_tab[i])
		i++;
	if ((ret = (char **)malloc(sizeof(char *) * i + 2)) == NULL)
		exit(printf("malloc read array failed\n"));
	ret[i + 1] = NULL;
	x = 0;
	ret[0] = ft_strdup(all->r_box.a_name);
	while (++x < i + 1)
		ret[x] = format_array(ret[0], x - 1, x == i ? '@' : 0);
	return (ret);
}

void					fill_array(t_all *all, char **cmd_tab, char **var_tab)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	creat_var(all, cmd_tab[i++], var_tab[j]);
	while (var_tab[j])
	{
		creat_var(all, cmd_tab[i], var_tab[j]);
		i++;
		j++;
	}
	creat_var(all, cmd_tab[i], all->r_box.full_string);
	ft_putchar('\n');
}
