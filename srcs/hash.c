/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:40:48 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 13:54:06 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			hash_bin(char *s)
{
	int		ret;
	int		ct;

	ret = 0;
	ct = 0;
	while (s[ct])
	{
		ret += s[ct];
		ct++;
	}
	ret %= 100;
	return (ret);
}

void		skip_collision(char **hash, int *ct)
{
	if (hash[*ct] == NULL)
		return ;
	else
	{
		(*ct)++;
		skip_collision(hash, ct);
	}
}

void		add_to_hash_table(t_all *all, char *bin)
{
	int		ret;

	ret = hash_bin(ft_strrchr(bin, '/') + 1);
	if (bin && ret < 250)
	{
		if (all->hash[ret] == NULL)
			all->hash[ret] = ft_strdup(bin);
		else
		{
			skip_collision(all->hash, &ret);
			all->hash[ret] = ft_strdup(bin);
		}
	}
}

int			hash_exist(char **hash, char *s)
{
	int		try;

	if ((!hash && !*hash) || (!s && !*s))
		return (0);
	try = hash_bin(s);
	if (hash[try] && ft_strcmp(hash[try], s))
		return (0);
	if (hash[try] != NULL && *hash[try])
		return (1);
	return (0);
}
