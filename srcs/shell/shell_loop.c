/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:26:13 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/04 10:26:14 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	display_prompt(t_all *all)
{
	tputs_termcap("ve");
	write(1, "$: ", 3);
	all->cursor_pos += PROMPT_LEN;
}

void	create_and_exec_command(t_all *all)
{
	create_cmd(all);
	(all->cmd[ft_strlen(all->cmd) - 1] == '\n') ?
		all->cmd[ft_strlen(all->cmd) - 1] = '\0' : write(1, "\0", 1);
	write(1, "\n", 1);
	if (all->cmd)
	{
		printf("cmd: |%s|\n", all->cmd);
		all->line2write += all->nb_lines;
	}
	if (!all->cmd[0] == 0 && ft_strlen(all->cmd) > 0)
	{
		add_to_history(all);
		parse_command(all, all->cmd);
		exec_command(all);
	}
	if (all->cmd_termcaps && ((t_cmd *)all->cmd_termcaps->head) && \
								((t_cmd *)all->cmd_termcaps->head)->c)
		del_dlist2(all->cmd_termcaps);
	all->line2write += all->nb_lines;
	// printf("lines: %d\n", all->line2write);
	if (all->cmd)
		ft_strdel(&all->cmd);
	loop(all);
}

static void	define_nb_lines(t_all *all)
{
	create_cmd(all);
	if (PROMPT_LEN + ((int)ft_strlen(all->cmd) - 1) == LINE_LEN * all->nb_lines)
		all->nb_lines++;
}

void	write_buffer(t_all *all)
{
	int		ct;

	ct = 0;
	ft_putstr(all->buff);
	if (ft_strlen(all->buff) > 1)
	{
		while (all->buff[ct])
		{
			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(all->buff[ct++]));
			all->cursor_pos++;
		}
	}
	else
	{
		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*all->buff));
		all->cursor_pos++;
	}
}

void	insert_char(t_all *all)
{
	all->already_open = 0;
	if (*all->buff == '$')
		all->lv += 1;
	tputs_termcap("im");
	if (all->cursor_pos - PROMPT_LEN < (int)all->cmd_termcaps->lenght \
													&& *all->buff != '\n')
	{
		if (*all->buff != '\n')
			write_buffer(all);
		update_cmd_line_insert(all, *all->buff);
		if (all->nb_lines >= 1)
			shift(all);
	}
	else
	{
		if (all->cursor_pos == all->ws.ws_col * all->curr_line)
			all->curr_line++;
		if (*all->buff != '\n')
			write_buffer(all);
	}
	tputs_termcap("ei");
}

void	read_keys(t_all *all)
{
	int		key;

	key = 0;
	if (read(0, all->buff, (MAXLEN - 1)) == -1)
		return ;
	if ((key = check_keys_arrows(all, all->buff)) < 0)
		return ;
	else if (key > 0)
		parse_keys(all);
	else
	{
		all->replace_cursor = 0;
		insert_char(all);
	}
}

void	init_loop(t_all *all)
{
	all->stop = 0;
	all->already_in_history = 0;
	all->already_in_select = 0;
	all->already_in_paste = 0;
	all->cursor_pos = 0;
	all->nb_lines = 1;
	all->curr_line = 1;
	all->index_history = all->pos_history;
	all->cmd_termcaps = all->p_mark ? all->p_mark : create_cmd_dlst();
	all->pcmd_t = NULL;
	all->pcmd_i = 0;
	all->buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	init_windows_size(all);
}

void	already_in_func(t_all *all)
{
	if (all->p_mark)
	{
		ft_putstr(all->cmd);
		all->cursor_pos = ft_strlen(all->cmd) + 1;
		all->cmd_termcaps->lenght = ft_strlen(all->cmd);
		all->p_mark = NULL;
	}
	if (!all->cmd)
	{
		if (!(all->cmd = (char *)malloc(sizeof(char) * MAXLEN - 1)))
			error("MALLOC");
	}
}

void	already_in_func_extended(t_all *all)
{
	if (all->buff)
	{
		ft_strdel(&all->buff);
		all->buff = ft_memset(ft_strnew(MAXLEN - 1),
			0, (MAXLEN - 1));
	}
	if (all->already_autocomplete && all->tmp_cmd)
	{
		realloc_termcaps_cmd(all, all->tmp_cmd);
		create_cmd(all);
		ft_putstr(all->cmd);
		if (all->replace_cursor > 0 && CURSOR > all->replace_cursor)
		{
			while (CURSOR-- > all->replace_cursor)
				tputs_termcap("le");
			tputs_termcap("le");
		}
		all->already_autocomplete = 0;
		ft_strdel(&all->tmp_cmd);
	}
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

void	get_cursor_row(t_all *all)
{
	int		fd;
	int		ct;
	char	*buff;
	char	*cpy;

	ct = 0;
	buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	cpy = ft_strnew(20);
	if ((fd = open("/dev/tty", O_RDWR)) == -1)
		write(1, "Open error\n", 12);
	ft_putstr_fd("\033[6n", fd);
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
			break ;
		}
	}
	parse_cursor_row(all, cpy);
	ft_strdel(&cpy);
}

void	loop(t_all *all)
{
	init_loop(all);
	(all->already_autocomplete) ? write(1, "\n", 1) : write(1, "\0", 1);
	display_prompt(all);
	already_in_func(all);
	while (*all->buff != '\n')
	{
		define_nb_lines(all);
		already_in_func_extended(all);
		read_keys(all);
	}
	if (all->cmd_termcaps && ((t_cmd *)all->cmd_termcaps->head) && \
								((t_cmd *)all->cmd_termcaps->head)->c)
	{
		if (all->lv)
			find_lv(all, all->lv);
		create_and_exec_command(all);
	}
	else
	{
		ft_putchar('\n');
		(loop(all));
	}
}
