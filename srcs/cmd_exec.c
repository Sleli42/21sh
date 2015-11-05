/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 11:03:01 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/05 11:03:03 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	exec_redirection_cmd(t_all *all, char *cmd)
{
	char						*cmp;
	int							i;
	static const	t_redirect	redirection[] =

	{{"|", create_pipe},
	{">", erase_and_replace},
	{">>", add_to_end},
	{"<", read_file},
	{"<<", read_stdin}};
	i = 0;
	(void)all;
	cmp = ft_strdup(my_strstr(cmd));
	if (cmp != NULL)
	{
		while (i < 5)
		{
			if (ft_strcmp(cmp, redirection[i].action_name) == 0)
			{
				ft_strdel(&cmp);
				redirection[i].f(all, cmd);
				return ;
			}
			i++;
		}
	}
}

void	exec_simple_cmd(t_all *all, char *cmd)
{
	int							i;
	int							stop;
	static const t_builtins		built[] =

	{{"env", env_display},
	{"set env", env_set},
	{"unset env", env_unset},
	{"pwd", pwd_display},
	{"cd", goto_dir},
	{"exit", free_all}};
	i = 0;
	stop = 0;
	while (i < 6)
	{
		if (ft_strncmp(cmd, built[i].action_name,
			ft_strlen(built[i].action_name)) == 0)
		{
			built[i].f(all, cmd);
			stop = 1;
		}
		i++;
	}
	if (!stop)
		exec_right_binary(all, ft_strsplit(cmd, ' '));
}

void	exec_command(t_all *all)
{
	int		i;

	i = 0;
	if (all->parsecmd != NULL)
	{
		while (all->parsecmd[i])
		{
			if (check_redirection(all->parsecmd[i]) == 1)
				exec_redirection_cmd(all, all->parsecmd[i]);
			else
				exec_simple_cmd(all, all->parsecmd[i]);
			i++;
		}
	}
}