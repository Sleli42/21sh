/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:23:54 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:23 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	display_array(char **array)
{
	int		ct;

	ct = 0;
	while (array[ct])
	{
		printf("array[ct]: [%s]\n", array[ct]);
		ct++;
	}
}

char	**replace_argv(char **array)
{
	 char	**ret;
	 int	ct;
	 int	ct2;

	 ct = 0;
	 ct2 = 0;
	 if (!array)
	 	return (NULL);
	 if (!(ret = (char **)malloc(sizeof(char *) * len_array(array))))
	 	return (NULL);
	 ret[ct++] = ft_strdup(array[len_array(array) - 1]);
	 while (array[ct2] && ct2 < 2)
	 	ret[ct++] = array[ct2++];
	 ret[ct] = NULL;
	 return (ret);
}

int		count_args(char **array, char *redir)
{
	int		ret;
	int		ct;

	ret = 0;
	ct = 0;
	while (array[ct])
	{
		if (!ft_strcmp(array[ct], redir))
			break ;
		ct++;
		ret++;
	}
	return (ret);
}

char	**rework_args_2_exec(char **array, char *redir)
{
	int		ct;
	int		stop;
	char	**ret;

	ct = 0;
	stop = count_args(array, redir);
	if (!(ret = (char **)malloc(sizeof(char *) * stop + 1)))
		return (NULL);
	while (array[ct] && ct < stop)
	{
		ret[ct] = ft_strdup(array[ct]);
		ct++;
	}
	ret[ct] = NULL;
	return (ret);
}

void	erase_and_replace(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		redirect = ft_strsplit(cmd, ' ');
		// display_array(redirect);
		// printf("len: %d\n", len_array(redirect));
		// printf("test: [%d]\n", redirect[0][0]);
		if (len_array(redirect) == 1 \
				|| (len_array(redirect) <= 2 && redirect[1][0] == '>'))
			return (redirection_error_2());
		if (len_array(redirect) <= 2 && redirect[0][0] == '>')
			return (redirection_error_4());
		if (len_array(redirect) == 3 && redirect[0][0] == '>')
			argv = replace_argv(redirect);
		(argv || *argv) ? del_array(&argv) : NULL;
		argv = rework_args_2_exec(redirect, ">");
		display_array(argv);
		// redirect[1] = ft_epur_str(redirect[1]);
		if ((all->fd2open = open(redirect[2], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return (redirection_error(redirect[2]));
		// argv = ft_strsplit(redirect[0], ' ');
		dupstdout = dup(1);
		dup_and_exec(all, argv, dupstdout, 1);
		redirect ? del_array(&redirect) : NULL;
		ft_putstr("YIIIH 2\n");
	}
}

void	add_to_end(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	redirect = ft_strsplit(cmd, '>');
	if ((!redirect[0][0]) || len_array(redirect) < 3)
		return (redirection_error_2());
	redirect[1] = ft_epur_str(redirect[1 + 1]);
	if ((all->fd2open = open(redirect[1], \
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return (redirection_error(redirect[1]));
	argv = ft_strsplit(redirect[0], ' ');
	dupstdout = dup(1);
	dup_and_exec(all, argv, dupstdout, 1);
	redirect ? del_array(&redirect) : NULL;
}

void	read_file(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdin;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		redirect = ft_strsplit(cmd, '<');
		if ((!redirect[0][0]) || len_array(redirect) < 2)
			return (redirection_error_2());
		redirect[1] = ft_epur_str(redirect[1]);
		if ((all->fd2open = open(redirect[1], O_RDONLY)) == -1)
			return (redirection_error(redirect[1]));
		argv = ft_strsplit(redirect[0], ' ');
		dupstdin = dup(0);
		dup_and_exec(all, argv, dupstdin, 0);
		redirect ? del_array(&redirect) : NULL;
	}
}

int		count_redirect(char *s)
{
	int		ct;
	int		ret;

	ct = 0;
	ret = 0;
	if (!s)
		return (0);
	while (s[ct])
	{
		if (s[ct] == '<')
		{
			while (s[ct] == '<')
			{
				ret++;
				if (ret > 2)
					return (ret);
				ct++;
			}
			ret = 0;
		}
		ct++;
	}
	return (ret);
}

void	read_stdin(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	char	*tmp_buff;

	argv = NULL;
	redirect = NULL;
	if (count_redirect(cmd) > 2)
		return (redirection_error_2());
	redirect = ft_strsplit(cmd, '<');
	argv = ft_strsplit(redirect[0], ' ');
	if (!redirect[0][0])
		return (redirection_error_4());
	while (1)
	{
		ft_putstr("> ");
		tmp_buff = read_stdin_cpy_buff();
		if (read_stdin_cmp_key(all, argv,
			ft_epur_str(redirect[1 + 1]), tmp_buff))
			break ;
		write(1, "\n", 1);
	}
	redirect ? del_array(&redirect) : NULL;
}
