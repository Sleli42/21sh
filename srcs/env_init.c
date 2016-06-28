/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:41:41 by lubaujar          #+#    #+#             */
/*   Updated: 2016/06/02 17:33:49 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

t_dlist				*dft_env(void)
{
	int				i;
	char			buf[512];
	t_dlist			*list_env;
	char			**dft_env;

	if ((dft_env = (char **)malloc(sizeof(char *) * 12)) == NULL)
		exit(1);
	dft_env[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	dft_env[1] = ft_strjoin("PWD=", getcwd(buf, 512));
	dft_env[2] = "SHLVL=1";
	dft_env[3] = "_=/usr/bin/env";
	dft_env[4] = "HOME=/nfs/2014/l/lubaujar";
	dft_env[5] = "TERM=xterm-256color";
	dft_env[6] = "TERM_PROGRAM=iTerm.app";
	dft_env[7] = "PAGER=less";
	dft_env[8] = "LESS=-R";
	dft_env[9] = "LC_CTYPE=";
	dft_env[10] = "LSCOLORS=Gxfxcxdxbxegedabagacad";
	dft_env[11] = NULL;
	list_env = NULL;
	i = -1;
	list_env = create_dlst();
	while (dft_env[++i])
		dlst_add_back(list_env, dlst_node_new(dft_env[i], (size_t)i));
	return (list_env);
}

void				init_inf(t_env_info *inf)
{
	inf->exec = 0x0;
	inf->unless = 0x0;
	inf->len = 0;
	inf->bin = NULL;
	inf->env_spe = NULL;
	inf->set_var = NULL;
	inf->bin_path = NULL;
}

t_dlist				*init_env(char **env)
{
	t_dlist			*list_env;
	int				i;

	if (!env || !*env)
		return (dft_env());
	list_env = NULL;
	i = -1;
	list_env = create_dlst();
	while (env[++i])
		dlst_add_back(list_env, dlst_node_new(env[i], (size_t)i));
	return (list_env);
}
