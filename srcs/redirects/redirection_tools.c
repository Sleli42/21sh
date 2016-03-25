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

void	redirection_error(char *file)
{
	ft_putstr("42shZer: no such file or directory: ");
	ft_putstr(file);
	ft_putchar('\n');
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
		dup_and_exec(all, argv, dupstdin, 0);
		return (1);
	}
	else
		tmp_buff ? ft_strdel(&tmp_buff) : NULL;
	return (0);
}
