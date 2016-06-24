/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_tools_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:06:36 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 16:47:44 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define ERROR_MSG	"\n42sh: Parse error"

void		check_glob(t_glob *g)
{
	if (g->err)
		return ;
	else if (g->sub != 0 || g->crush != 0 || g->c_indx != 0 || g->quote != 0 ||\
		g->d_quote != 0)
		g->err = g->err && *g->err ? g->err : ft_strdup(ERROR_MSG);
}

void		save_glob(t_all *all, t_glob *g)
{
	if (*all->buff == '(' || *all->buff == ')')
		g->sub += *all->buff == '(' ? 1 : -1;
	else if (*all->buff == '{' || *all->buff == '}')
		g->crush += *all->buff == '{' ? 1 : -1;
	else if (*all->buff == '[' || *all->buff == ']')
		g->c_indx += *all->buff == '[' ? 1 : -1;
	else if (*all->buff == '\'')
		g->quote += g->quote ? -1 : 1;
	else if (*all->buff == '\"')
		g->d_quote += g->d_quote ? -1 : 1;
	else if (*all->buff == '\\')
		g->back += g->back ? -1 : 1;
	if (g->sub < 0 || g->crush < 0 || g->c_indx < 0)
		g->err = ft_strdup(ERROR_MSG);
}

void		create_and_exec_command(t_all *all)
{
	char		*tmp;

	create_cmd(all);
	f_cpy(all);
	(all->cmd[ft_strlen(all->cmd) - 1] == '\n') ?
	all->cmd[ft_strlen(all->cmd) - 1] = '\0' : write(1, "\0", 1);
	write(1, "\n", 1);
	tmp = ft_epur_str(all->cmd);
	all->cmd || *all->cmd ? ft_strdel(&all->cmd) : NULL;
	all->cmd = ft_strdup(tmp);
	tmp || *tmp ? ft_strdel(&tmp) : NULL;
	if (all->cmd[0] != 0 && ft_strlen(all->cmd) > 0)
	{
		parse_command(all, all->cmd);
		all->parsecmd && all->parsecmd[0] ? exec_command(all) : NULL;
		add_to_history(all);
	}
	!CMD_NULL ? del_dlist2(all->cmd_termcaps) : NULL;
	all->cmd || *all->cmd ? ft_strdel(&all->cmd) : NULL;
	loop(all);
}

void		write_buffer(t_all *all)
{
	int		ct;

	ct = 0;
	if (all->globing.dt_print | all->globing.cr_split)
	{
		*&all->globing.cr_split = 0x0;
		*&all->globing.dt_print = 0x0;
	}
	else
		ft_putstr(all->buff);
	if (ft_strlen(all->buff) > 1)
	{
		while (all->buff[ct])
		{
			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(all->buff[ct]));
			CURSOR++;
			ct++;
		}
	}
	else
	{
		dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*all->buff));
		CURSOR++;
	}
}

// void		display_cmd(t_all *all, int stop)
// {
// 	while (all->cmd[CURSOR - PROMPT_LEN])
// 	{
// 		if (CURSOR == all->curr_line * LINE_LEN)
// 		{
// 				// exit(1);
// 			// printf("YES\n");
// 			tputs_termcap("do");
// 			all->curr_line++;
// 		}
// 		ft_putchar(all->cmd[CURSOR - PROMPT_LEN]);
// 		CURSOR++;
// 	}
// 	// printf("CURSOR: %d\n", CURSOR);
// 	// printf("stop: %d\n", stop);
// 	// printf("len: %d\n", (int)all->cmd_termcaps->lenght);
// 	while (CURSOR > stop)
// 	{
// 		goto_left(all);
// 		// if (all->curr_line > 1 && CURSOR == ((all->curr_line - 1) * LINE_LEN) + 1)
// 		// {
// 		// 	// tputs_termcap("up");
// 		// 	all->curr_line--;
// 		// }
// 		// tputs_termcap("le");
// 		// CURSOR--;
// 	}
// }

void		new_shift(t_all *all)
{
	// ft_putchar('|');
	// printf("\n\n\nchar2insert: [ %c ]\n", c2insert);
	// printf("cursor: %d\n", CURSOR);
	// printf("all->cmd[cursor]: [ %c ]\n", all->cmd[CURSOR]);
	// printf("all->cmd[cursor - prompt]: [ %c ]\n", all->cmd[CURSOR - PROMPT_LEN]);
	// printf("all->cmd[cursor - len]: [ %c ]\n", all->cmd[CURSOR - ft_strlen(all->buff)]);
	// printf("all->cmd[cursor - len - prompt]: [ %c ]\n", all->cmd[CURSOR - ft_strlen(all->buff) - PROMPT_LEN]);
	// exit(1);

	int		save = CURSOR;
	// printf("\n\ncurrLine: %d\n", all->curr_line);
	// printf("nbLines: %d\n", all->nb_lines);
	CURSOR -= LINE_LEN * (all->curr_line - 1);
	while (all->curr_line < all->nb_lines)
	{
		tputs_termcap("do");
		all->curr_line++;
	}
	while (all->curr_line > 1)
	{
		tputs_termcap("ce");
		tputs_termcap("cb");
		tputs_termcap("up");
		all->curr_line--;
	}
	while (CURSOR-- > PROMPT_LEN)
		tputs_termcap("le");
	// printf("\n\nCURSOR: %d\n", CURSOR);
	display_prompt(all);
	create_cmd(all);
	CURSOR = (int)all->cmd_termcaps->lenght;
	// printf("\n\ncurrLine: %d\n", all->curr_line);
	// printf("CURSOR: %d\n", CURSOR);
	// printf("&& save: %d\n", save);
	// exit(1);
	// printf("len cmd: %d\n", (int)all->cmd_termcaps->lenght);
	// printf("\n\n[%s]\n", all->cmd);
	// display_cmd(all, save);
	ft_putstr(all->cmd);
	/* replace cursor */
	while (CURSOR > save - PROMPT_LEN)
	{
		tputs_termcap("le");
		CURSOR--;
	}
	CURSOR += PROMPT_LEN;
	all->curr_line = 1;
	define_current_line(all);
}

void		insert_char(t_all *all)
{
	all->already_open = 0;
	if (*all->buff == '$')
		all->lv += 1;
	tputs_termcap("im");
	// printf("CURSOR - prompt: %d\n", CURSOR - PROMPT_LEN);
	// printf("len cmd: %d\n", (int)all->cmd_termcaps->lenght);
	if ((CURSOR - PROMPT_LEN) < (int)all->cmd_termcaps->lenght \
		&& *all->buff != '\n')
	{
		// ft_putchar('*');
		if (*all->buff != '\n')
			all->globing.cr_split ? (all->globing.cr_split = 0) : \
												ft_putstr(all->buff);
		if (ft_strlen(all->buff) > 1)
		{
			int		ct = 0;
			while (all->buff[ct])
			{
				update_cmd_line_insert(all, all->buff[ct]);
				ct++;
			}
		}
		else
			update_cmd_line_insert(all, *all->buff);
		if (all->nb_lines >= 1)
		{
			if (ft_strlen(all->buff) > 1)
				new_shift(all);
			else
				shift(all);
		}
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
