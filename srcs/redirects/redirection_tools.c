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
			// printf("ret: |%s|\n", ret);
	}
	return (ret);
}

void	exec_agg1(t_all *all, char *cmd)
{
	char	**split_agg;
	char	**split_2exec;
	char	*file;
	int		dupout = dup(1);
	int		duperr = dup(2);

	cmd = rework_cmd_agg1(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	file = get_good_file_agg1(split_agg);
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
			// printf("ret: |%s|\n", ret);
	}
	return (ret);
}

int		check_error_agg2(char **split, char *file)
{
	while (split && ft_strcmp(*split, ">&"))
		split++;
	if (ft_isdigit(file[0]) && ft_atoi(file) > 2)
	{
		ft_putstr("sh: ");
		ft_putnbr(ft_atoi(file));
		ft_putstr(": Bad file descriptor\n");
		return (1);
	}
	else if (ft_isdigit(*(split - 1)[0]) && ft_atoi(*(split - 1)) > 2)
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
		{
			// if (ft_isdigit(*(array + 1)[0]))
			// 	return (NULL);
			// else
				return (*(array + 1));
		}
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
		if (ft_isdigit(*split_agg[0]) && !ft_strcmp(*(split_agg + 1), ">&"))
			split_agg++;
		if (ft_isdigit(*(split_agg)[0]) && !ft_strcmp(*(split_agg - 1), ">&"))
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
	int		dupout = dup(1);
	int		duperr = dup(2);

	split_2exec = NULL;
	file = NULL;
	cmd = rework_cmd_agg2(cmd);
	split_agg = ft_strsplit(ft_epur_str(cmd), ' ');
	file = get_good_file_agg2(split_agg);
	// printf("file fd: |%s|\n", file);
	if (!check_error_agg2(split_agg, file))
	{
		split_2exec = create_argv_cmd_agg2(split_agg, file);
		// display_array(split_2exec);
		if (!ft_isdigit(file[0]))
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
			exec_right_binary(all, split_2exec);
		del_array(&split_2exec);
	}
	del_array(&split_agg);
}

void	exec_aggregations(t_all *all, char *cmd)
{
	// int		fd2dup;
	// int		fd2back;
	// // char	**split;
	// char	*file;

	(void)all;
	// fd2dup = 0;
	// fd2back = 0;
	// file = NULL;
	// split = ft_strsplit(cmd, ' ');
	char	*tmp;

	tmp = ft_strchr(cmd, '>');
	// cmd = ft_strchr(cmd, '>');
	if (*tmp == '>' && *(tmp - 1) == '&')
	{
		exec_agg1(all, cmd);
		// del_array(&split);

	}
	else if (*tmp == '>' && *(tmp + 1) == '&')
		exec_agg2(all, cmd);
	// ls -l &> test; cat test
	// total 178
	// -rwxr-xr-x   1 lubaujar  2014_paris  70012 Feb 19 11:36 42sh
	// -rw-r--r--   1 lubaujar  2014_paris   3492 Feb 17 15:33 Makefile
	// display_array(split);
	// printf("c - 1: |%c|\n", *(cmd - 1));
	// printf("c + 1: |%c|\n", *(cmd + 1));
	// if (ft_isdigit(*(cmd - 1))) /* file descriptor 2 dup */
	// 	fd2dup = *(cmd - 1) - '0';
	// if (*(cmd + 1) == '&') 		/* file descriptor 2 replace */
	// 	fd2back = *(cmd + 2) - '0';
	// else						/* file 2 replace */
	// {
	// 	split = ft_strsplit(cmd, ' ');
	// 	display_array(split);
	// }
}

/*
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
