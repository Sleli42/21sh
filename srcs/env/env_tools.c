/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:17:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 10:17:42 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*find_env_arg(t_all *all, char *arg2find)
{
	t_node		*nav;

	nav = all->env->head;
	if (nav)
	{
		while (nav)
		{
			if (ft_strncmp(nav->s, arg2find, ft_strlen(arg2find)) == 0)
				return (nav->s);
			nav = nav->next;
		}
	}
	return (NULL);
}

char		**ft_dupenv(char **env)
{
	char	**dup;
	int		i;

	i = -1;
	if (!(dup = (char **)malloc(sizeof(char *) * ft_tablen(env) + 1)))
		return (NULL);
	while (++i < (int)ft_tablen(env))
		dup[i] = ft_strdup(env[i]);
	dup[++i] = NULL;
	return (dup);
}