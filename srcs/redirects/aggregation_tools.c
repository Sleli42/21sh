/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:11:28 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/07 13:11:29 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
	tests:
			- touch riri; rm riri; cat riri 2>&-
			- ls -l 1>&-; ls -X 2>&-; ls -laX >&-; ls -l 2>&-
			- echo lol taratata 2>&-; echo taratata 1>&-; echo lol 3>&-

			- ls 1>&2; ls 2>&1; ls 1>&5
			- echo -X test 2>&1; echo -X test 1>&2; echo -X test 5>&4

			- ls -l &> file 2; cat file; rm file; cat file 2>&-



	possibilities: 
			- fd>&fd
			- X>&fd -> fd bad, if not open
			- cmd >& file 		== 	fd > file
			- badCmd 1>& file 	== 	fd > file
			- cmd &> file 		== 	fd > file

	errors:
			- badCmd 2>& file -> bash: file: ambiguous redirect


				test fd: int fcntl(int fd, int cmd);
						  				(fd, F_GETFD) == -1 -> error bad fd
	==========================================================
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
	==========================================================
				cat -p 2>&file
						-->	bash: file: ambiguous redirect
				cat -p > file
						-->	cat: illegal option -- p
						-->	usage: cat [-benstuv] [file ...]
				cat -p >& file
						-->	error cat > file
				cat -p 2>&1
						-->	cat: illegal option -- p
						-->	usage: cat [-benstuv] [file ...]
				cat -p 2>&3
						-->	bash: 3: Bad file descriptor

*/

int		check_aggregations(char *cmd)
{
	int		ct;

	ct = 0;
	while (cmd[ct++] && cmd)
	{
		if ((cmd[ct] == '&' && cmd[ct + 1] == '>')
			|| (cmd[ct] == '>' && cmd[ct + 1] == '&')
			|| (cmd[ct] == '<' && cmd[ct + 1] == '&'))
			return (1);
	}
	return (0);
}

char	*check_file_in_cmd(char *cmd)
{
	while (cmd && *cmd)
	{
		if (*cmd == '>' || *cmd == '<' || *cmd == '&')
			return (NULL);
		cmd++;
	}
	return (cmd);
}

int		count_arg_agg(char **array, char *file)
{
	int		ret;

	ret = 0;
	while (array && *array)
	{
		if ((ft_strcmp(*array, "&>") && ft_strcmp(*array, file))
			|| (ft_strcmp(*array, ">&") && ft_strcmp(*array, file))
			|| (ft_strcmp(*array, "<&") && ft_strcmp(*array, file)))
			ret++;
		array++;
	}
	return (ret);
}

void	close_fd(t_all *all, char *fd2close)
{
	if (ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 0)
		;
	else if ((ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 1)
		|| !ft_isdigit(fd2close[0]))
	{
		all->fd2restore = 1;
		close(STDOUT_FILENO);
	}
	else if ((ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 2))
	{
		all->fd2restore = 2;
		close(STDERR_FILENO);
	}
}

void	exec_aggregations(t_all *all, char *cmd)
{
	char	*tmp;

	tmp = ft_strchr(cmd, '>');
	if (tmp)
	{
		if (*tmp == '>' && *(tmp - 1) == '&')
			exec_agg1(all, cmd);
		else if (*tmp == '>' && *(tmp + 1) == '&')
			exec_agg2(all, cmd);
	}
	else
	{
		tmp = ft_strchr(cmd, '<');
		if (*tmp == '<' && *(tmp + 1) == '&')
			exec_agg3(all, cmd);
	}
}