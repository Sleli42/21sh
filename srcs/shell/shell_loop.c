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
}

void	create_and_exec_command(t_all *all)
{
	create_cmd(all);
	(all->cmd[ft_strlen(all->cmd) - 1] == '\n') ?
		all->cmd[ft_strlen(all->cmd) - 1] = '\0' : write(1, "\0", 1);
	write(1, "\n", 1);
	if (all->cmd)
		printf("cmd: |%s|\n", all->cmd);
	if (!all->cmd[0] == 0 && ft_strlen(all->cmd) > 0)
	{
		add_to_history(all);
		parse_command(all, all->cmd);
		exec_command(all);
	}
	(all->cmd_termcaps) ? del_dlist2(all->cmd_termcaps) : NULL;
	//reset_term();
	loop(all);
}

void	loop(t_all *all)
{
	char	*buff;
	int		key;

	all->stop = 0;
	all->already_open = 0;
	all->already_in_history = 0;
	all->cursor_pos = 1;
	all->curr_line = 1;
	all->index_history = all->pos_history;
	all->cmd_termcaps = create_cmd_dlst();
	// init_term();
	//tputs_termcap("mm");
	display_prompt(all);
	// int auto_wrap;
	// if ((auto_wrap = tgetflag("HC")) == 0)
	// 	ft_putstr("FAIL TGETFLAG\n");
	// printf("wrap: %d\n", auto_wrap);
	if (!all->cmd)
	{
		if (!(all->cmd = (char *)malloc(sizeof(char) * MAXLEN - 1)))
			error("MALLOC");
	}
	// if (all->already_autocomplete)
	// {
	// 	if (all->tmp_cmd != NULL)
	// 	{
	// 		realloc_termcaps_cmd(all, all->tmp_cmd);
	// 		ft_putstr(all->tmp_cmd);
	// 		ft_strdel(&all->tmp_cmd);
	// 	}
	// 	del_clist(&all->list_dir);
	// }
	///buff = (char *)malloc(sizeof(char *));
	buff = ft_strnew(MAXLEN - 1);
	ft_memset(buff, 0, (MAXLEN - 1));
	//tputs_termcap("ti");
	//tputs_termcap("mi");
	while (*buff != '\n')
	{
		if ((all->curr_line == 1 && all->cursor_pos + 2 == all->ws.ws_col)
			|| (all->curr_line > 1 
				&& (all->cursor_pos / all->curr_line) == all->ws.ws_col))
		{
			all->curr_line++;
			//printf("line: %d\n", all->curr_line);
		}
		if (buff)
		{
			ft_strdel(&buff);
			buff = ft_strnew(MAXLEN - 1);
			ft_memset(buff, 0, (MAXLEN - 1));
		}
		read(0, buff, (MAXLEN - 1));
		// read_key(buff);
		// break ;
		if ((key = check_keys_arrows(all, buff)) < 0)
			break ;
		else if (key > 0)
			parse_keys(all);
		else
		{
			//tputs_termcap("am");
			tputs_termcap("im");
			// if (*buff == '/')
			// {
			// 	if (all->nav_dir)
			// 		add_to_cmd(all, (all->nav_dir->prev) ? all->nav_dir->prev->arg : all->nav_dir->arg);
			// 	all->already_open = 0;
			// }
			// if (all->already_in_history)
			// {
			// 	realloc_termcaps_cmd(all, all->cmd);
			// 	//create_cmd(all);
			// 	ft_strdel(&all->current);
			// 	all->is_history = 1;
			// 	all->stop = 0;
			// }
			//printf("pos cursor: %d\n", all->cursor_pos);
			if ((size_t)all->cursor_pos <= all->cmd_termcaps->lenght && *buff != '\n')
			{
				if (*buff != '\n')
					ft_putchar(*buff);
				update_cmd_line_insert(all, *buff);
			}
			else
			{
				//printf("|%d| && |%d|\n", buff[0], buff[1]);
				if (*buff != '\n')
				{
					ft_putchar(*buff);
					dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*buff));
					all->cursor_pos++;
				}
			}
			tputs_termcap("ei");
		}
	}
	create_and_exec_command(all);
}