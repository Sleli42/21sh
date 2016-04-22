/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 11:03:01 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:30 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

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
	cmp = my_strstr(all, cmd);
	if (cmp != NULL)
	{
		while (i < 5)
		{
			if (!ft_strcmp(cmp, redirection[i].action_name))
				redirection[i].f(all, cmd);
			i++;
		}
	}
	cmp ? ft_strdel(&cmp) : NULL;
}

void	simple_cmd_loop(t_all *all, t_builtins built[11], char *cmd)
{
	int		i;
	int		stop;
	char	*tmp;

	i = 0;
	stop = 0;
	while (i < 11)
	{
		tmp = (i == 2 && symbol_in_cmd(cmd, '=')) ? cmd + count_var_len(cmd) : cmd;
		if (!ft_strncmp(tmp, built[i].action_name, \
						ft_strlen(built[i].action_name)))
		{
			built[i].f(all, cmd);
			stop = 1;
		}
		i++;
	}
	if (!stop)
	{
		if (!ft_strncmp(cmd, "./", 2))
			check_mode_file(all, cmd);
		exec_right_binary(all, ft_strsplit(cmd, ' '));
	}
}

void	exec_simple_cmd(t_all *all, char *cmd)
{
	static const t_builtins		built[] =
	{{"env", env_display},
	{"set env", env_set},
	{"=", env_modify},
	{"unset env", env_unset},
	{"pwd", pwd_display},
	{"cd", goto_dir},
	{"exit", free_all},
	{"!", built_mark},
	{"history", built_history},
	{"read", read_built},
	{"echo", built_echo}};

	simple_cmd_loop(all, (t_builtins *)built, cmd);
}

void	exec_command(t_all *all)
{
	int		i;

	i = 0;
	while (all->parsecmd[i][0] == 0)
		i++;
	if (all->parsecmd && all->parsecmd[i] && all->parsecmd[i][0])
	{
		while (all->parsecmd[i] && *(all->parsecmd[i]))
		{
			if (check_redirection(all->parsecmd[i]) == 1)
				exec_redirection_cmd(all, all->parsecmd[i]);
			else
				exec_simple_cmd(all, all->parsecmd[i]);
			i++;
		}
	}
}
