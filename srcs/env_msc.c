/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_msc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 11:05:21 by skhatir           #+#    #+#             */
/*   Updated: 2016/06/20 23:35:32 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

char				**check_format(char *cmd)
{
	char			**ret;

	if (!cmd || !*cmd)
		return (NULL);
	ret = NULL;
	if (!(ret = ft_strsplit(cmd, ' ')))
		return (NULL);
	if (ft_tablen(ret) != 2)
	{
		del_array(&ret);
		ft_putendl("Bad format: set env [var] [content]");
		return (NULL);
	}
	else
		return (ret);
}

char				**ft_tabdelone(char **array, char *s)
{
	char			**newtab;
	int				i;

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

char				*dup_comp(char *target, char **array)
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

char				**ft_tabjoin(char **dupenv, char **env_spe)
{
	char			**tabcpy;
	int				i;
	int				j;

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

void				ft_printtab(char **array)
{
	int				i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		ft_putendl(array[i]);
		i++;
	}
}
