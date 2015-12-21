/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 02:17:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/12/21 02:17:22 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int		lu_putchar(int c)
{
	ft_putchar(c);
	return (0);
}

void	tputs_termcap(char *tc)
{
	char	*res;

	if ((res = tgetstr(tc, NULL)) == NULL)
		return ;
	tputs(res, 0, lu_putchar);
}

void	init_term(void)
{
	char	*term_name;
	struct termios	term;

	term_name = NULL;
	if (tgetent(NULL, term_name) == -1)
		write(1, "error\n", 6);
		// term_error("TGETENT");
	if ((term_name = getenv("TERM=")) == NULL)
		write(1, "error\n", 6);
		//term_error("GETENV");
	if (tcgetattr(0, &term) == -1)
		// term_error("TCGETATTR");
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		write(1, "error\n", 6);
		// term_error("TCSETATTR");
}

void	restore_term(t_termios restore)
{
	tputs_termcap("ve");
	if (tcgetattr(0, &restore) == -1)
		write(1, "error\n", 6);
		// term_error("TCGETATTR");
	if (tcsetattr(0, 0, &restore) == -1)
		write(1, "error\n", 6);
		// term_error("TCSETATTR");
}

void	create_cmd(t_all *all)
{
	t_cmd	*nav;
	int		i;

	nav = all->cmd_termcaps->head;
	i = 0;
	if (all->cmd)
		ft_strdel(&all->cmd);
	if (!(all->cmd = (char *)malloc(sizeof(char) * len_lst_cmd(all->cmd_termcaps->head) + 1)))
		write(1, "error\n", 6);
	if (nav)
	{
		while (nav)
		{
			all->cmd[i++] = nav->c;
			nav = nav->next;
		}
		all->cmd[i] = '\0';
	}
}

int		check_keys_arrows(t_all *all, char buff[3])
{
	if (K_ENTER)
	{
		tputs_termcap("me");
		return (-1);
	}
	else if (K_RIGHT || K_LEFT)
	{
		return (2);
	}
	return (0);
}

void	make_moves(t_all *all, char buff[3])
{
	if (K_LEFT && all->cmd_termcaps->lenght > 0
		&& all->cursor >= 1)
	{
		tputs_termcap("le");
	}
	else if (K_RIGHT && all->cmd_termcaps->lenght > 0
		&& all->cursor <= (int)all->cmd_termcaps->lenght + 1)
	{
		tputs_termcap("nd");
	}
}

void	loop(t_all *all)
{
	char	buff[MAXLEN];
	int		key;

	all->cmd_termcaps = create_cmd_dlst();
	all->cursor = 1;
	ft_memset(buff, 0, MAXLEN - 1);
	write(1, "$: ", 3);
	while (*buff != '\n')
	{
		read(0, buff, MAXLEN);
		//printf("%d\n", *buff);
		if ((key = check_keys_arrows(all, buff)) < 0)
			break ;
		else if (key > 0)
			make_moves(all, buff);
		else
		{
			dlst_add_back_2(all->cmd_termcaps, dlst_cmd_new(*buff));
			ft_putchar(*buff);
			all->cursor++;
		}
	}
	display_dlst(all->cmd_termcaps);
	printf("cursor pos: %d\n", all->cursor);
	create_cmd(all);
	printf("cmd: |%s|\n", all->cmd);
	del_dlist2(all->cmd_termcaps);
	loop(all);
}

int		main(int ac, char **av)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	init_term();
	loop(all);
	restore_term(all->restore);
	return (0);
}