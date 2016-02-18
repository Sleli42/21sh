/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 23:43:01 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 23:43:02 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	dup_and_exec(t_all *all, char **cmd_argv, int fd2back, int fd2dup)
{
	dup2(all->fd2open, fd2dup);
	close(all->fd2open);
	exec_right_binary(all, cmd_argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
	del_array(&cmd_argv);
}

int		check_aggregations(char *cmd)
{
	int		ct;

	ct = 0;
	while (cmd[ct++] && cmd)
	{
		if ((cmd[ct] == '>' && ft_isdigit(cmd[ct - 1])) \
				|| (cmd[ct] == '>' && cmd[ct + 1] == '&') \
				|| (cmd[ct] == '<' && ft_isdigit(cmd[ct - 1])) \
				|| (cmd[ct] == '<' && cmd[ct + 1] == '&'))
			return (1);
	}
	return (0);
}

void	display_array(char **array)
{
	if (array && *array)
	{
		while (*array)
		{
			printf("[ %s ]\n", *array);
			array++;
		}
	}
}

void	exec_aggregations(t_all *all, char *cmd)
{
	int		fd2dup;
	int		fd2back;
	char	**split;
	char	*file;

	(void)all;
	fd2dup = 0;
	fd2back = 0;
	file = NULL;
	split = ft_strsplit(cmd, ' ');
	cmd = ft_strchr(cmd, '>');
	display_array(split);
	// printf("c - 1: |%c|\n", *(cmd - 1));
	// printf("c + 1: |%c|\n", *(cmd + 1));
	if (ft_isdigit(*(cmd - 1))) /* file descriptor 2 dup */
		fd2dup = *(cmd - 1) - '0';
	if (*(cmd + 1) == '&') 		/* file descriptor 2 replace */
		fd2back = *(cmd + 2) - '0';
	// else						/* file 2 replace */
	// {
	// 	split = ft_strsplit(cmd, ' ');
	// 	display_array(split);
	// }
}

/*




				-- if (ls -l 1>&2)	==
						-->	ls -l 1 (dup) > 2
						--> ls -l stdout (dup) stderr
				-- if (1>&fd) && !fd
						--> bad file descriptor -> error
				-- if (NULL>&fd) && fd
						--> NULL = stdout par defaut
				-- if (NULL>&file)
						--> NULL = stdout && stderr
	==========================================================
			ls -l 1>& file -a  ==
						--> ls -l -a > file































*/
