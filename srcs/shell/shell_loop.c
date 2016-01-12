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
	all->already_in_select = 0;
	all->cursor_pos = 1;
	all->nb_lines = 1;
	all->index_history = all->pos_history;
	all->cmd_termcaps = create_cmd_dlst();
	display_prompt(all);
	if (!all->cmd)
	{
		if (!(all->cmd = (char *)malloc(sizeof(char) * MAXLEN - 1)))
			error("MALLOC");
	}
	buff = ft_strnew(MAXLEN - 1);
	ft_memset(buff, 0, (MAXLEN - 1));
	//tputs_termcap("ti");
	//tputs_termcap("mi");
	while (*buff != '\n')
	{
		if ((all->nb_lines == 1 && all->cursor_pos + 2 == all->ws.ws_col)
			|| (all->nb_lines > 1 
				&& (all->cursor_pos / all->nb_lines) == all->ws.ws_col))
		{
			all->nb_lines++;
			//printf("line: %d\n", all->nb_lines);
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
			if ((size_t)all->cursor_pos <= all->cmd_termcaps->lenght && *buff != '\n')
			{
				if (*buff != '\n')
					ft_putchar(*buff);
				update_cmd_line_insert(all, *buff);
				if (all->nb_lines >= 1)
				{
					shift(all);
				}

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