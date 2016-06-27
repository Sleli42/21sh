/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 23:43:01 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:15 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	dup_and_exec(t_all *all, char **cmd_argv, int fd2back, int fd2dup)
{
	dup2(all->fd2open, fd2dup);
	close(all->fd2open);
	exec_right_binary(all, cmd_argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
}

char	*my_strstr(t_all *all, char *s)
{
	char	*tmp;
	char	*ret;
	int		i;

	tmp = s;
	ret = NULL;
	i = 0;
	(void)all;
	while (tmp[i])
	{
		if (ret)
			return (ret);
		if (tmp[i] == '|')
			ret = ft_strdup("|");
		else if (tmp[i] == '>')
			ret = (tmp[i + 1] == '>') ? ft_strdup(">>") : ft_strdup(">");
		else if (tmp[i] == '<')
			ret = (tmp[i + 1] == '<') ? ft_strdup("<<") : ft_strdup("<");
		i++;
	}
	return (ret);
}

char	*read_stdin_cpy_buff(void)
{
	char	*buff;
	char	*tmp_buff;
	int		i;

	buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	tmp_buff = ft_strnew(MAXLEN - 1);
	i = 0;
	while (read(0, buff, (MAXLEN - 1)) != -1)
	{
		if (*buff == '\n')
			break ;
		ft_putchar(*buff);
		tmp_buff[i++] = *buff;
	}
	tmp_buff[i] = '\0';
	return (tmp_buff);
}

int		read_stdin_cmp_key(t_all *all, char **argv, char *key, char *tmp_buff)
{
	int		dupstdin;

	if (!ft_strcmp(key, tmp_buff))
	{
		dupstdin = dup(0);
		write(1, "\n", 1);
		close(all->fd2open);
		if ((all->fd2open = open(".tmp_file", O_RDONLY, 0644)) == -1)
			return (0);
		(!all->err) ? dup_and_exec(all, argv, dupstdin, 0) : NULL;
		return (1);
	}
	else
		(tmp_buff && *tmp_buff) ? ft_strdel(&tmp_buff) : NULL;
	return (0);
}

void	exec_double_redirection(t_all *all, char **array)
{
	char	**argv;
	int		fd;
	int		dupstdin;
	int		dupstdout;

	argv = rework_args_2_exec(array, first_redirect(array));
	if ((all->fd2open = open(get_fd_2_open(array, "<"), \
		O_RDONLY, 0644)) == -1)
		return (redirection_error(get_fd_2_open(array, "<")));
	if ((fd = open(get_fd_2_open(array, ">"), \
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (redirection_error(get_fd_2_open(array, ">")));
	dupstdin = dup(0);
	dupstdout = dup(1);
	dup2(fd, 1);
	(!all->err) ? dup_and_exec(all, argv, dupstdin, 0) : NULL;
	close(fd);
	dup2(dupstdout, 1);
	close(dupstdout);
	array ? del_array(&array) : NULL;
}
