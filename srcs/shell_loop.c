/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 10:26:13 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 18:58:51 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"
#define G_		(all->globing.crush && all->globing.sub)
#define G_ALL	(all->globing.back | all->globing.crush | all->globing.sub)
#define G_ALL2	(all->globing.quote | all->globing.d_quote)

int		check_globbing(t_all *all)
{
	int		i;

	i = 0;
	if (*all->buff == '\n' && (G_ALL || G_ALL2 > 0))
	{
		*all->buff = all->globing.crush ? ';' : '.';
		all->globing.back ? all->globing.back-- : 0;
		all->globing.esc_mem += CURSOR - PROMPT_LEN;
		all->cursor_pos = PROMPT_LEN;
		ft_putstr("\n > ");
		all->globing.cr_split = 0x1;
		return (*all->buff == ';' ? *all->buff : 0);
	}
	while (GLOB[i])
	{
		if (GLOB[i++] == *all->buff)
		{
			save_glob(all, &all->globing);
			ft_putstr(all->buff);
			*all->buff = ' ';
			*&all->globing.dt_print = 0x1;
		}
	}
	return (1);
}

void	read_keys(t_all *all)
{
	int		key;
	int		cr;

	key = 0;
	cr = 0;
	if (read(0, all->buff, (MAXLEN - 1)) == -1)
		return ;
	if ((cr = check_globbing(all)))
	{
		if (*all->buff == 4)
			control_d(all);
		else if ((key = check_keys_arrows(all, all->buff)) < 0)
			return ;
		else if (key > 0)
			parse_keys(all);
		else if (check_str(all->buff))
		{
			all->replace_cursor = 0;
			insert_char(all);
		}
	}
}

void	already_in_func(t_all *all)
{
	create_cmd(all);
	if (all->p_mark && all->cmd)
	{
		ft_putstr(all->cmd);
		all->cursor_pos = ft_strlen(all->cmd) + 1;
		all->cmd_termcaps->lenght = ft_strlen(all->cmd);
		all->p_mark = NULL;
	}
	all->cmd = !all->cmd ? ft_strnew(MAXLEN - 1) : NULL;
	if (!all->already_autocomplete && all->tmp_cmd)
	{
		realloc_termcaps_cmd(all, all->tmp_cmd);
		create_cmd(all);
		ft_putstr(all->cmd);
		all->tmp_cmd ? ft_strdel(&all->tmp_cmd) : NULL;
	}
	// if (all->already_in_search)
	// 	all->cmd_search_str = all->cmd;
}

void	already_in_func_extended(t_all *all)
{
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
		if (all->replace_cursor > 0 && CURSOR > all->replace_cursor)
		{
			while (CURSOR-- > all->replace_cursor)
				tputs_termcap("le");
			tputs_termcap("le");
		}
		all->already_autocomplete = 0;
		all->tmp_cmd ? ft_strdel(&all->tmp_cmd) : NULL;
	}
}

void	loop(t_all *all)
{
	init_loop(all);
	init_glob(all);
	display_prompt(all);
	already_in_func(all);
	f_cpy(all);
	while (*all->buff != '\n')
	{
		define_nb_lines(all);
		already_in_func_extended(all);
		read_keys(all);
	}
	check_glob(&all->globing);
	if (!CMD_NULL && !all->globing.err)
	{
		(all->lv) ? find_lv(all) : NULL;
		all->prog_exec = 1;
		create_and_exec_command(all);
	}
	else
	{
		check_glob(&all->globing);
		all->globing.err ? ft_putendl(all->globing.err) : ft_putchar('\n');
		all->globing.err ? ft_strdel(&all->globing.err) : NULL;
		loop(all);
	}
}
