/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_msc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 11:05:21 by skhatir           #+#    #+#             */
/*   Updated: 2016/05/31 11:09:44 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char	**ft_tabdelone(char **array, char *s)
{
	char	**newtab;
	int		i;

	newtab = NULL;
	if (array && ft_tablen(array) > 1)
	{
		i = 0;
		newtab = (char **)malloc(sizeof(char *) * ft_tablen(array));
		while (*array)
		{
			if (!(ft_strncmp(*array, s, ft_strlen(s))))
				array++;
			if (!*array)
				break ;
			newtab[i] = ft_strdup(*array);
			array++;
			i++;
		}
		newtab[i] = NULL;
	}
	return (newtab);
}

char	*dup_comp(char *target, char **array)
{
	int				i;
	char			*ret;

	i = 0;
	ret = NULL;
	while (array && array[i])
	{
		if (!ft_strncmp(target, array[i], count_var_len(array[i])))
		{
			ret = ft_strdup(array[i]);
			array = ft_tabdelone(array, array[i]);
			i++;
		}
		else
			i++;
	}
	return ((ret = ft_strdup(target)));
}

char	**ft_tabjoin(char **dupenv, char **env_spe)
{
	char	**tabcpy;
	int		i;
	int		j;

	tabcpy = NULL;
	if ((tabcpy = (char **)malloc(sizeof(char *) * \
							(ft_tablen(dupenv) + ft_tablen(env_spe) + 1))))
	{
		i = 0;
		j = 0;
		while (dupenv[i])
		{
			tabcpy[i] = dup_comp(dupenv[i], env_spe);
			i++;
		}
		while (env_spe[j])
		{
			tabcpy[i++] = ft_strdup(env_spe[j++]);
		}
		tabcpy[i] = NULL;
	}
	return (tabcpy);
}

void	ft_printtab(char **array)
{
	int				i;

	i = 0;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
}
