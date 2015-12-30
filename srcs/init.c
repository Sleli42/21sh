/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 16:12:58 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/03 16:12:59 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char		**ft_dupenv(char **env)
{
	char	**dup;
	int		i;

	i = -1;
	if (!(dup = (char **)malloc(sizeof(char *) * ft_tablen(env) + 1)))
		return (NULL);
	while (++i < (int)ft_tablen(env))
		dup[i] = ft_strdup(env[i]);
	dup[++i] = NULL;
	return (dup);
}

t_dlist		*init_env(char **env)
{
	t_dlist	*list_env;
	int		i;

	list_env = NULL;
	i = -1;
	list_env = create_dlst();
	while (env[++i])
		dlst_add_back(list_env, dlst_node_new(env[i], (size_t)i));
	return (list_env);
}

// void		fct_sig(int sig)
// {
// 	if (sig == SIGINT || sig == SIGCONT)
// 		display_prompt(f_cpy(NULL));
// 	else
// 		exit(0);
// }

// static void		catch_sig(void)
// {
// 	signal(SIGINT, fct_sig);
// 	signal(SIGCONT, fct_sig);
// }

int		init_tty(void)
{
	int		tty;

	if ((tty = ttyslot()) == -1)
		return (-1);
	if (isatty(tty) == 0)
		return (NOTATTY);
	return (tty);
}

void	init_windows_size(t_all *all)
{
	if (ioctl(init_tty(), TIOCGWINSZ, &all->ws) == -1)
		term_error("ioctl");
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

void 	reset_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		term_error("TCGETATTR");
	term.c_lflag |= ~(ECHO | ICANON);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		term_error("TCSETATTR");
}

t_all		*init_all(char **env)
{
	t_all	*all;

	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error("MALLOC");
	//catch_sig();
	//init_termios(all->term);
	init_windows_size(all);
	all->env = init_env(env);
	all->dupenv = ft_dupenv(env);
	all->cmd_history = create_dlst();
	// all->cmd = create_cmd_dlst();
	all->path2exec = ft_strsplit(find_env_arg(all, "PATH") + 5, ':');
	all->parsecmd = NULL;
	all->pipe = NULL;
	all->nav = NULL;
		// --HISTORY
	// if ((all->fd2open = open(redirect[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	if ((all->fd_history = open(".21sh_history", O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		write(1, "open error\n", 11);
	all->history_buff = parse_history();
	all->pos_history = check_history_file(all->history_buff);
	all->tmp_cmd = NULL;
	// all->file_history = ft_strdup(".21sh_history");
	return (all);
}
