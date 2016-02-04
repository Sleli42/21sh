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

void	display_prompt(t_all *all) {
	(void)all;
	//tputs_termcap("me");
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
		//printf("--> %d\n", all->line2write);
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
	//reset_term();
	all->line2write += all->nb_lines;
	loop(all);
}

static void	define_nb_lines(t_all *all)
{
	// ft_putstr("STOP0");
	create_cmd(all);
	// ft_putstr("STOP1");
	///printf("rows: %d\n", all->ws.ws_row);
	if (PROMPT_LEN + ((int)ft_strlen(all->cmd) - 1) == LINE_LEN * all->nb_lines)
		all->nb_lines++;
}

void	insert_char(t_all *all)
{
	all->already_open = (*all->buff == ' ') ? 0 : all->already_open;
	if (*all->buff == '$')
		all->lv += 1;
	tputs_termcap("im");
	if (all->cursor_pos - PROMPT_LEN < (int)all->cmd_termcaps->lenght && *all->buff != '\n')
	{
		if (*all->buff != '\n')
			ft_putchar(*all->buff);
		update_cmd_line_insert(all, *all->buff);
		if (all->nb_lines >= 1)
			shift(all);
	}
	else
	{
		if (all->cursor_pos == all->ws.ws_col * all->curr_line)
			all->curr_line++;
		if (*all->buff != '\n')
		{
			ft_putchar(*all->buff);
			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*all->buff));
			all->cursor_pos++;
		}
	}
	tputs_termcap("ei");
}

void	read_keys(t_all *all)
{
	int		key;

	key = 0;
	if (read(0, all->buff, (MAXLEN - 1)) == -1)
		return ;
	// read(0, all->buff, (MAXLEN - 1));
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

void	loop(t_all *all)
{
	// int		key = 0;

	all->stop = 0;
	all->already_in_history = 0;
	all->already_in_select = 0;
	all->cursor_pos = 0;
	all->nb_lines = 1;
	all->curr_line = 1;
	all->index_history = all->pos_history;
	all->cmd_termcaps = all->p_mark ? all->p_mark : create_cmd_dlst();
	all->pcmd_t = NULL;
	all->pcmd_i = 0;
	(all->list_dir) ? del_clist(&all->list_dir) : NULL;
	(all->already_autocomplete) ? write(1, "\n", 1) : write(1, "\0", 1);
	display_prompt(all);
	// printf("yPixel: %d\n", all->ws.ws_ypixel);
	init_windows_size(all);
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
	// all->buff = ft_strnew(MAXLEN - 1);
	all->buff = ft_memset(ft_strnew(MAXLEN - 1), 0, (MAXLEN - 1));
	//tputs_termcap("ti");
	//tputs_termcap("mi");
	while (*all->buff != '\n')
	{
		// ft_putstr("HERE0\n");
		// if (0)
			define_nb_lines(all);
		
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
			// printf("repalce: %d\n", all->replace_cursor);
			if (all->replace_cursor > 0 && CURSOR > all->replace_cursor)
			{
				while (CURSOR-- > all->replace_cursor)
					tputs_termcap("le");
				tputs_termcap("le");
			}
			// all->replace_cursor = 0;
			/* replace cursor */
			all->already_autocomplete = 0;
		}
		read_keys(all);
		// ft_putstr("HERE\n");
		// read(0, all->buff, (MAXLEN - 1));
		// //line_edition(all, all->buff);
		// // read_key(all->buff);
		// // break ;
		// if ((key = check_keys_arrows(all, all->buff)) < 0)
		// 	break ;
		// else if (key > 0)
		// 	parse_keys(all);
		// else
		// {
		// 	tputs_termcap("im");
		// 	if (all->cursor_pos - PROMPT_LEN < (int)all->cmd_termcaps->lenght && *all->buff != '\n')
		// 	{
		// 		if (*all->buff != '\n')
		// 			ft_putchar(*all->buff);
		// 		//write(1, "here\n", 5);
		// 		update_cmd_line_insert(all, *all->buff);
		// 		if (all->nb_lines >= 1)
		// 			shift(all);
		// 	}
		// 	else
		// 	{
		// 		if (all->cursor_pos == all->ws.ws_col * all->curr_line)
		// 			all->curr_line++;
		// 		if (*all->buff != '\n')
		// 		{
		// 			ft_putchar(*all->buff);
		// 			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*all->buff));
		// 			all->cursor_pos++;
		// 		}
		// 	}
		// 	tputs_termcap("ei");	
		// }
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
	// create_and_exec_command(all);
}