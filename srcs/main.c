 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 15:59:16 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 15:59:18 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi
*/
/*
void	display_tab(char **tab) {
	while (tab && *tab)
		printf("[%s]\n", *tab++);
}
*/
void		read_key(void) {
	char	buff[3] = {0};

	read(0, buff, 3);
	if (K_UP || K_DOWN)
		printf("GO TO HISTORY\n");
	else if (K_RIGHT || K_LEFT || K_DELETE || K_SPACE)
		printf("GO TO DIRECTION\n");
	else
		printf("CHAR\n");
}

void	display_prompt(t_all *all) {
	(void)all;
	write(1, "$: ", 3);
}

void 	reset_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		term_error("TCGETATTR");
	term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		term_error("TCSETATTR");
}

void	init_term(void)
{
	char	*term_name;
	struct termios	term;

	term_name = NULL;
	if (tgetent(NULL, term_name) == -1)
		term_error("TGETENT");
	if ((term_name = getenv("TERM=")) == NULL)
		term_error("GETENV");
	if (tcgetattr(0, &term) == -1)
		term_error("TCGETATTR");
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		term_error("TCSETATTR");
}

void	loop(t_all *all)
{
	int		r;
	char	buff[MAXLEN];

	r = 0;
	//f_cpy(all);
	while (1091111096051)
	{
		//display_prompt(all);
		write(1, "$: ", 3);
		ft_memset(buff, 0, ft_strlen(buff));
		if ((r = read(0, buff, (MAXLEN - 1))) == -1)
			return ;
		init_term();
		read_key();
		reset_term();
		printf("%d\n", r);
		printf("%s\n", buff);
		buff[r - 1] = '\0';
		if (r == 0)
			return ;
		if (r > 0)
		{
			parse_command(all, buff);
			exec_command(all);
		}
		//tputs_termcap("ei");
	}
}

int		main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	all = init_all(env);
	loop(all);
	restore_term(all->restore);
	write(1, "\n", 1);
	exit(1);
	return (0);
}