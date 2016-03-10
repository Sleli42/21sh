/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:41:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 10:41:42 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_dlist		*init_env(char **env)
{
	t_dlist	*list_env;
	int		i;

	list_env = NULL;
	i = -1;
	list_env = create_dlst();
	while (env[++i])
		dlst_add_back(list_env, dlst_node_new(env[i], (size_t)i));
	return (list_env);
}
