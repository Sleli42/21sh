/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:12:29 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/04 17:12:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	exec_redirection_cmd(char *cmd)
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
	cmp = ft_strdup(my_strstr(cmd));
	if (cmp != NULL)
	{
		while (i < 5)
		{
			if (ft_strcmp(cmp, redirection[i].action_name) == 0)
			{
				ft_strdel(cmp);
				redirection[i].f(cmd);
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
			built[i].f(all);
			stop = 1;
		}
		i++;
	}
	if (!stop)
		exec_binary();
}

void	exec_command(t_all *all)
{
	int		i;

	i = 0;
	while (all->parsecmd[i])
	{
		if (check_redirection(all->parsecmd[i]) == 1)
			exec_redirection_cmd(all->parsecmd[i]);
		else
			exec_simple_cmd(all->parsecmd[i]);
		i++;
	}
}

void	parse_command(t_all *all, char *buff)
{
	int		i;

	i = 0;
	all->parsecmd = NULL;
	if (buff[0] != '\0')
		all->parsecmd = ft_strsplit(buff, ';');
	if (all->parsecmd)
		while (all->parsecmd[i])
			all->parsecmd[i] = ft_epur_str(all->parsecmd[i]);
}

int		check_redirection(char *s)
{
	if (s && *s)
	{
		while (*s)
		{
			if (*s == '>' || *s == '<' || *s == '|'
				|| (*s == '>' && (*s + 1) == '>')
				|| (*s == '<' && (*s + 1) == '<'))
				return (1);
			s++;
		}
	}
	return (0);
}