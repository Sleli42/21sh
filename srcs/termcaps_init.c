/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 17:46:08 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:05:28 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

static char	*get_env_var(char **dupenv, char *var)
{
	int		i;

	i = 0;
	if (dupenv && *dupenv)
	{
		while (dupenv[i])
		{
			if (!ft_strncmp(dupenv[i], var, ft_strlen(var)))
				return (dupenv[i] + ft_strlen(var));
			i++;
		}
	}
	return (NULL);
}

void		init_term(char **dupenv)
{
	char			*term_name;
	struct termios	term;

	term_name = NULL;
	if ((term_name = get_env_var(dupenv, "TERM=")) == NULL)
		term_error("GETENV");
	printf("termname: |%s|\n", term_name);
	if (tgetent(NULL, term_name) == -1)
		term_error("TGETENT");
	if (tcgetattr(0, &term) == -1)
		term_error("TCGETATTR");
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		term_error("TCSETATTR");
}

void		init_windows_size(t_all *all)
{
	if (ioctl(init_tty(), TIOCGWINSZ, &all->ws) == -1)
		term_error("ioctl");
	all->max_rows = tgetnum("li");
}

int			init_tty(void)
{
	int		tty;

	if ((tty = ttyslot()) == -1)
		return (-1);
	if (isatty(tty) == 0)
		return (NOTATTY);
	return (tty);
}
