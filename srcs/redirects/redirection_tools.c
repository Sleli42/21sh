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
		// if ((cmd[ct] == '>' && ft_isdigit(cmd[ct - 1])) \
		// 		|| (cmd[ct] == '>' && cmd[ct + 1] == '&') \
		// 		|| (cmd[ct] == '<' && ft_isdigit(cmd[ct - 1])) \
		// 		|| (cmd[ct] == '<' && cmd[ct + 1] == '&'))
		if ((cmd[ct] == '&' && cmd[ct + 1] == '>')
			|| (cmd[ct] == '>' && cmd[ct + 1] == '&')
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

char	*get_good_file_agg1(char **array)
{
	while (array && *array)
	{
		if (!ft_strcmp(*array, "&>"))
			return (*(array + 1));
		array++;
	}
	return (NULL);
}

int		count_arg_agg(char **array, char *file)
{
	int		ret;

	ret = 0;
	while (array && *array)
	{
		if ((ft_strcmp(*array, "&>") && ft_strcmp(*array, file))
			|| (ft_strcmp(*array, ">&") && ft_strcmp(*array, file)))
			ret++;
		array++;
	}
	return (ret);
}

char	**create_argv_cmd_agg1(char **split_agg, char *file)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * \
					count_arg_agg(split_agg, file) + 1)))
		error("MALLOC");
	while (split_agg && *split_agg)
	{
		if (ft_strcmp(*split_agg, "&>") && ft_strcmp(*split_agg, file))
			ret[i++] = ft_strdup(*split_agg);
		split_agg++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*rework_cmd_agg1(char *cmd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_strnew(ft_strlen(cmd) + 20);
	if (ret && cmd)
	{
		while (cmd[i])
		{
			if ((cmd[i] == '&' && cmd[i - 1] != ' ')
				|| (cmd[i - 1] == '>' && cmd[i] != ' ')
				|| (cmd[i - 1] == '<' && cmd[i] != ' '))
				ret[j++] = ' ';
			ret[j++] = cmd[i++];
		}
		ret[j] = '\0';
	}
	return (ret);
}

void	exec_agg1(t_all *all, char *cmd)
{
	char	**split_agg;
	char	**split_2exec;
	char	*file;
	int		dupout;
	int		duperr;

	cmd = rework_cmd_agg1(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	file = get_good_file_agg1(split_agg);
	dupout = dup(1);
	duperr = dup(2);
	if ((all->fd2open = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		write(1, "err0r1\n", 6);
	split_2exec = create_argv_cmd_agg1(split_agg, file);
	dup2(all->fd2open, 1);
	dup2(all->fd2open, 2);
	close(all->fd2open);
	exec_right_binary(all, split_2exec);
	dup2(dupout, 1);
	dup2(duperr, 2);
	del_array(&split_agg);
	del_array(&split_2exec);
}

char	*rework_cmd_agg2(char *cmd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_strnew(ft_strlen(cmd) + 20);
	if (ret && cmd)
	{
		while (cmd[i])
		{
			if ((cmd[i] == '>' && cmd[i - 1] != ' ')
				|| (cmd[i - 1] == '&' && cmd[i] != ' '))
				ret[j++] = ' ';
			ret[j++] = cmd[i++];
		}
		ret[j] = '\0';
	}
	return (ret);
}

int		check_error_agg2(t_all *all, char **split, char *file)
{
	while (split && ft_strcmp(*split, ">&"))
		split++;
	if (!ft_strcmp(*(split + 1), "-"))
		close_fd(all, *(split - 1));
	else if (ft_isdigit(file[0]) && ft_atoi(file) > 2)
	{
		ft_putstr("sh: ");
		ft_putnbr(ft_atoi(file));
		ft_putstr(": Bad file descriptor\n");
		return (1);
	}
	else if ((ft_isdigit(*(split - 1)[0]) && ft_atoi(*(split - 1)) > 2
		&& ft_strcmp(file, "-")) || !ft_isdigit(*(split + 1)[0]))
	{
		ft_putstr("sh: ");
		ft_putstr(file);
		ft_putstr(": ambiguous redirect\n");
		return (1);
	}
	return (0);
}

char	*get_good_file_agg2(char **array)
{
	while (array && *array)
	{
		if (!ft_strcmp(*array, ">&"))
			return (*(array + 1));
		array++;
	}
	return (NULL);
}

char	**create_argv_cmd_agg2(char **split_agg, char *file)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	if (!(ret = (char **)malloc(sizeof(char *) * \
					count_arg_agg(split_agg, file) + 1)))
		error("MALLOC");
	while (split_agg && *split_agg)
	{
		if (*(split_agg + 1) && ft_isdigit(*split_agg[0]) \
								&& !ft_strcmp(*(split_agg + 1), ">&"))
			split_agg++;
		if (*(split_agg + 1) && ft_isdigit(*split_agg[0]) \
								&& !ft_strcmp(*(split_agg - 1), ">&"))
			split_agg++;
		if (ft_strcmp(*split_agg, ">&") && ft_strcmp(*split_agg, file))
			ret[i++] = ft_strdup(*split_agg);
		split_agg++;
	}
	ret[i] = NULL;
	return (ret);
}

void	exec_agg2(t_all *all, char *cmd)
{
	char	**split_agg;
	char	**split_2exec;
	char	*file;
	int		dupout;
	int		duperr;
	int		tmp_fd;

	split_2exec = NULL;
	file = NULL;
	cmd = rework_cmd_agg2(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	file = get_good_file_agg2(split_agg);
	dupout = dup(1);
	duperr = dup(2);
	// display_array(split_agg);
	// printf("file fnd: |%s|\n", file);
	if (!check_error_agg2(all, split_agg, file))
	{
		split_2exec = create_argv_cmd_agg2(split_agg, file);
		// display_array(split_2exec);
		if (!ft_isdigit(file[0]) && ft_strcmp(file, "-"))
		{
			if ((all->fd2open = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
				write(1, "err0r1\n", 6);
			dup2(all->fd2open, 1);
			dup2(all->fd2open, 2);
			close(all->fd2open);
			exec_right_binary(all, split_2exec);
			dup2(dupout, 1);
			dup2(duperr, 2);
		}
		else
		{
			exec_right_binary(all, split_2exec);
			if (all->fd2restore >= 1 && all->fd2restore <= 2)
			{
				tmp_fd = dup(all->fd2restore);
				dup2((all->fd2restore == 1) ? dupout : duperr, all->fd2restore);
				all->fd2restore = 0;
			}
			// else if (all->fd2restore > 2)
			// {
			// 	dup2(dupout, 1);
			// 	dup2(duperr, 2);
			// 	all->fd2restore = 0;
			// }
		}
		(split_2exec) ? del_array(&split_2exec) : NULL;
	}
	(split_agg) ? del_array(&split_agg) : NULL;
}

void	close_agg(t_all *all, char *cmd, char c)
{
	int		fd;
	int		dupfd;

	if (ft_isdigit(c))
	{
		fd = c - 48;
		if (fd > 2)
			exec_agg2(all, cmd);
		else
		{
			if (fcntl(fd, F_GETFD) != -1)
			{
				dupfd = (fd == 2) ? dup(2) : dup(1);
				close(fd);
				(fd == 2) ? dup2(dupfd, STDERR_FILENO) \
								: dup2(dupfd, STDOUT_FILENO);
			}
		}
	}
}

void	close_fd(t_all *all, char *fd2close)
{
	if ((ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 1)
		|| !ft_isdigit(fd2close[0]))
	{
		all->fd2restore = 1;
		close(STDOUT_FILENO);
	}
	else if ((ft_isdigit(fd2close[0]) && ft_atoi(fd2close) == 2))
	{
		all->fd2restore = 2;
		// ft_putstr("OK tout va bien ne suis la \n");
		close(STDERR_FILENO);
	}
	// else if (!ft_isdigit(fd2close[0]))
	// {
	// 	all->fd2restore = 3;
	// 	close(STDOUT_FILENO);
	// 	close(STDERR_FILENO);
	// }
}

// void	close_agg2(t_all *all, char *cmd, char c)
// {
// 	int		fd;
// 	int		dupfd;

// 	dupfd = dup(0);
// 	// if (ft_isdigit(c))
// 	// {
// 	// 	fd = c - 48;
// 	// 	if (fd == 0)
// 	// 		exec_agg2(all, cmd);
// 	// 	else
// 	// 	{
// 	// 		if (fcntl(fd, F_GETFD) != -1)
// 	// 		{
// 	// 			dupfd = (fd == 2) ? dup(2) : dup(1);
// 	// 			close(fd);
// 	// 			(fd == 2) ? dup2(dupfd, STDERR_FILENO) \
// 	// 							: dup2(dupfd, STDOUT_FILENO);
// 	// 		}
// 	// 	}
// 	// }
// }


char	*my_strstr(t_all *all, char *s)
{
	char	*tmp;
	char	*ret;
	int		i;

	tmp = s;
	i = 0;
	all->inpipe = 0;
	all->inredir = 0;
	while (tmp[i])
	{
		// (s[i] == '>' && s[i + 1] == ' ') ? return(ft_strdup(">") : return(NULL));
		if (tmp[i] == '|')
			all->inpipe = 1;
		else if (tmp[i] == '>')
		{
			all->inredir = 1;
			if (tmp[i + 1] == '>' && tmp[i + 2] == ' ')
				ret = ft_strdup(">>");
			else
				ret = ft_strdup(">");
		}
		else if (tmp[i] == '<')
		{
			all->inredir = 1;
			if (tmp[i + 1] == '<' && tmp[i + 2] == ' ')
				ret = ft_strdup("<<");
			else
				ret = ft_strdup("<");
		}
		i++;
	}
	return (ret);
}


void	exec_aggregations(t_all *all, char *cmd)
{
	char	*tmp;

	// ft_putstr("OUAIIIIIIIIIIs\n\n\n\n");
	// tmp = ft_strdup(cmd);
	tmp = ft_strchr(cmd, '>');
	if (tmp)
	{
		// if (*(tmp + 1) == '&' && *(tmp + 2) == '-')
			// close_agg(all, cmd, *(tmp - 1));
		// printf("tmp - 1: |%c|\n", *(tmp - 1));
		if (*tmp == '>' && *(tmp - 1) == '&')
			exec_agg1(all, cmd);
		else if (*tmp == '>' && *(tmp + 1) == '&')
			exec_agg2(all, cmd);
	}
	else
	{
		tmp = ft_strchr(tmp, '<');
		if (*(tmp + 1) == '&' && *(tmp + 2) == '-')
			exec_agg2(all, cmd);
	}
	// (tmp != NULL) ? ft_strdel(&tmp) : NULL;
}

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
