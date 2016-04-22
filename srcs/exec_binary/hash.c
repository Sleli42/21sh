/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:40:48 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:29:44 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			hash_bin(char *s)
{
	int		ret;

	ret = 0;
	while (*s)
	{
		ret += *s;
		s++;
	}
	ret %= 100;
	return (ret);
}

void		add_to_hash_table(t_all *all, char *bin)
{
	int		ret;

	ret = hash_bin(ft_strrchr(bin, '/') + 1);
	if (bin && ret < 250)
	{
		if (!all->hash[ret])
			all->hash[ret] = ft_strdup(bin);
		else
		{
			while (all->hash[ret] != NULL && ret < 250)
				ret++;
			all->hash[ret] = ft_strdup(bin);
		}
	}
}

int			hash_exist(char **hash, char *s)
{
	int		try;

	try = hash_bin(s);
	if (hash[try] && *hash[try])
		return (1);
	return (0);
}
