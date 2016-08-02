/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:06:30 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:01:59 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	display_prompt(t_all *all)
{
	(all->already_autocomplete) ? write(1, "\n", 1) : write(1, "\0", 1);
	ft_putstr(all->prompt);
	all->cursor_pos += PROMPT_LEN;
}

void	define_nb_lines(t_all *all)
{
	create_cmd(all);
	if (PROMPT_LEN + ((int)ft_strlen(all->cmd) - 1) == LINE_LEN * all->nb_lines)
		all->nb_lines++;
}

void	parse_cursor_row(t_all *all, char *buff)
{
	char	tmp[2];
	int		ct;
	int		i;

	ct = 0;
	i = 1;
	while (buff[i] && buff[i] != ';')
		tmp[ct++] = buff[i++];
	tmp[ct] = 0;
	all->curr_row = ft_atoi(tmp);
}

char	*get_cursor_row_loop(char *buff)
{
	char	*cpy;
	int		ct;

	cpy = ft_strnew(MAXLEN - 1);
	ct = 0;
	while (*buff != '\n')
	{
		if ((read(0, buff, (MAXLEN - 1))) == -1)
			write(1, "Read error\n", 12);
		if (buff[0] == '\033')
		{
			buff++;
			while (buff[ct])
			{
				cpy[ct] = buff[ct];
				ct++;
			}
			cpy[ct] = 0;
			return (cpy);
		}
	}
	return (cpy);
}

void	get_cursor_row(t_all *all)
{
	int		fd;
	char	*buff;
	char	*cpy;

	buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	if ((fd = open("/dev/tty", O_RDWR)) == -1)
		write(1, "Open error\n", 12);
	ft_putstr_fd("\033[6n", fd);
	cpy = get_cursor_row_loop(buff);
	parse_cursor_row(all, cpy);
	close(fd);
	ft_strdel(&cpy);
}
