/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 18:26:08 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/07 18:26:10 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*

tputs_termcap("cd") -> efface jusqu'a la fin de l'ecran

*/

void		debug(t_all *all)
{
	printf("\npromptLen: %d\n", PROMPT_LEN);
		printf("strLen: %d\n", (int)ft_strlen(all->cmd));
		printf("ws_col: %d\n", LINE_LEN);
		printf("nbLine: %d\n", all->nb_lines);
		printf("cuurLine: %d\n", all->curr_line);
		printf("all->cmd: %s\n", all->cmd);
		printf("strLen: [ %c ]\n", all->cmd[ft_strlen(all->cmd)]);
		printf("strLen - 1: [ %c ]\n", all->cmd[ft_strlen(all->cmd) - 1]);
		printf("strLen - promptLen: [ %c ]\n", all->cmd[(int)ft_strlen(all->cmd) - PROMPT_LEN]);
		printf("(strLen - 1) - promptLen: [ %c ]\n", all->cmd[((int)ft_strlen(all->cmd) - 1) - PROMPT_LEN]);
		printf("ws_col * currLine: [ %c ]\n", all->cmd[LINE_LEN * all->curr_line]);
		printf("ws_col * nbLine: [ %c ]\n", all->cmd[LINE_LEN * all->nb_lines]);
		printf("ws_col * currLine - promptLen: [ %c ]\n", all->cmd[(LINE_LEN * all->curr_line) - PROMPT_LEN]);
	// mcol * curr_line) - 1]);
}

void	shift_first_char(t_all *all, int curr_line)
{
	while (CURSOR++ < (curr_line * LINE_LEN))
		tputs_termcap("nd");
	write(1, &all->cmd[(curr_line * LINE_LEN) - 4], 1);
	tputs_termcap("do");
	tputs_termcap("dc");
}

void	shift_last_char(t_all *all, int curr_line)
{
	char	save_char;
	int		ct;

	ct = CURSOR;
	ct += (all->nb_lines - all->curr_line > 1) ? 1 : 0;
	// printf("currLine + ws.col: %d\n", (LINE_LEN * curr_line));
	while (ct < (LINE_LEN * curr_line))
		ct++;
	//ct += (all->nb_lines - all->curr_line > 1) ? 1 : 0;
	save_char = all->cmd[(ct - PROMPT_LEN)];
	// printf("save: [ %c ]\n", save_char);
	tputs_termcap("do");
	write(1, &save_char, 1);
}

void	shift(t_all *all)
{
	int		save;
	int		ct;

	create_cmd(all);
	ct = 0;
	/* char == EOL */
	if (PROMPT_LEN + ((int)ft_strlen(all->cmd) - 1) == (LINE_LEN * all->nb_lines))
	{
		// write(1, "ok\n", 3);
		tputs_termcap("sc");
		if (all->nb_lines - all->curr_line == 0)
		{	/* shift last char */
			all->line2write += 1;
			tputs_termcap("do");
			write(1, &all->cmd[ft_strlen(all->cmd) - 1], 1);
		}
		else
		{
			save = all->curr_line;
			while (all->nb_lines - save > 0)
			{
				write(1, "here\n\n", 6);
				shift_last_char(all, save++);
			}
			/* shift last char of line */
		}
		tputs_termcap("rc");
	}
	else if (CURSOR == (LINE_LEN * all->curr_line))
	{
		/* cursor == EOL */
		save = all->curr_line;
		while (all->nb_lines - save > 0)
		{
			tputs_termcap("do");
			write(1, &all->cmd[CURSOR - PROMPT_LEN], 1);
			tputs_termcap("le");
			save++;
			ct++;
		}
		while (ct-- > 1)
			tputs_termcap("up");
		all->curr_line++;
	}
	else if (all->curr_line < all->nb_lines && all->nb_lines - all->curr_line > 0)
	{
		ct = all->curr_line;
		tputs_termcap("sc");
		while (all->nb_lines - ct > 0)
			shift_last_char(all, ct++);
		tputs_termcap("rc");
	}
}