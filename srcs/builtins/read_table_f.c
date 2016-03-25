/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_table_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:11:32 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:07:40 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int						check_digit(char *s)
{
	int					i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return ((s[i] ? 0x0 : 0x1));
}

int						ft_u(t_all *all, char *n)
{
	int					ret;

	ret = 0;
	if (!check_digit(n))
		return (-1);
	if ((all->r_box.fd = ft_atoi(n)) > 255)
		return (BAD_FD);
	return (2);
}

int						ft_ft(t_all *all, int f, char *next_cm)
{
	int					(*type_func)(t_all *all, char *n);
	static int			(*arg_func[])(t_all *all, char *n) =
	{ft_u,
	ft_t,
	ft_p,
	ft_a,
	ft_n,
	ft_d};

	type_func = (f - 4) >= 0 ? arg_func[f - 4] : NULL;
	return ((type_func != NULL ? type_func(all, next_cm) : -1));
}

int						check_requiere(int f, char **cmd_tab, int i, t_all *all)
{
	if (!cmd_tab[0] || !cmd_tab[1] || !cmd_tab[1][0] || cmd_tab[0][i + 1])
	{
		all->r_box.err = BAD_FORMAT;
		return (-1);
	}
	return (ft_ft(all, f, cmd_tab[1]));
}
