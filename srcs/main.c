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
void		read_key(char *cmd) {
	char	buff[3] = {0};

	read(0, buff, 3);
	if (K_UP || K_DOWN)
		printf("GO TO HISTORY\n");
	else if (K_RIGHT || K_LEFT || K_DELETE || K_SPACE)
		printf("GO TO DIRECTION\n");
	else
		ft_putstr(cmd);
}

void	display_prompt(t_all *all) {
	(void)all;
	tputs_termcap("ve");
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
	/* lire une touche [ fleches, backspace .. ] */
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		term_error("TCSETATTR");
}
/*
void	loop(t_all *all)
{
	int		r;
	char	buff[MAXLEN];

	r = 0;
	//f_cpy(all);
	init_term();
	while (1091111096051)
	{
		display_prompt(all);
		//write(1, "$: ", 3);
		ft_memset(buff, 0, ft_strlen(buff));
		if ((r = read(0, buff, (MAXLEN - 1))) == -1)
			return ;
		if (K_UP || K_DOWN)
			printf("GO TO HISTORY\n");
		else if (K_RIGHT || K_LEFT || K_DELETE || K_SPACE)
			printf("GO TO DIRECTION\n");
		else
			ft_putchar(buff[r]);
		//read_key(buff);
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
	reset_term();
}
*/

void	display_dlst(t_dlist2 *lst) {
	t_cmd	*tmp = lst->head;

	while (tmp) {
		printf("\n[%c]*pos: '%zu'", tmp->c, tmp->pos);
		tmp = tmp->next;
	}
}

void	loop(t_all *all)
{
	char	buff[MAXLEN];
	char	*cmd;
	int		i;
	int		key;

	i = 0;
	all->cmd = create_cmd_dlst();
	display_prompt(all);
	if (!(cmd = (char *)malloc(sizeof(char) * MAXLEN - 1)))
		error("MALLOC");
	ft_memset(buff, 0, MAXLEN - 1);
	while (*buff != '\n')
	{
		read(0, buff, (MAXLEN - 1));
		if ((key = check_keys_arrows(buff)) < 0)
			break ;
		else
		{
			ft_putchar(*buff);
			cmd[i++] = *buff;
			dlst_add_back_2(all->cmd, dlst_cmd_new(*buff, (size_t)i));
		}
	}
	if (cmd[i - 1] == 10)
		cmd[i - 1] = 0;
	else
		cmd[i] = 0;
	write(1, "\n", 1);
	dlst_add_back(all->cmd_history, dlst_node_new(cmd));
	// printf("|%s|\n", cmd);
	if (cmd && i > 1)
	{
		parse_command(all, cmd);
		exec_command(all);
		ft_strdel(&cmd);
	}
	loop(all);
}

int		main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	all = init_all(env);
	init_term();
	loop(all);
	del_dlist(all->env);
	del_dlist(all->cmd_history);
	restore_term(all->restore);
	write(1, "\n", 1);
	exit(1);
	return (0);
}