/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 08:36:04 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/10 08:36:06 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int		binary_operators(char **array, int *nb_bin_ope)
{
	int		ct;

	ct = 0;
	while (array[ct])
	{
		if (!ft_strncmp(array[ct], "&&", 2) || !ft_strncmp(array[ct], "||", 2))
			*nb_bin_ope = *nb_bin_ope + 1;
		ct++;
	}
	if (*nb_bin_ope > 0)
		return (1);
	return (0);
}

void	and_operator(char **parsecmd, int *ct, int err)
{
	if (err == 256)
	{
		while (parsecmd[*ct])
		{
			if (!ft_strcmp(parsecmd[*ct], "||"))
				break ;
			*ct = *ct + 1;
		}
		*ct = (*ct != len_array(parsecmd)) ? *ct + 1 : *ct;
	}
	else
		*ct = (*ct != len_array(parsecmd)) ? *ct + 1 : *ct;
}

void	or_operator(char **parsecmd, int *ct, int err)
{
	if (err == 256)
	{
		while (parsecmd[*ct])
		{
			if (!ft_strcmp(parsecmd[*ct], "||"))
				break ;
			*ct = *ct + 1;
		}
		*ct = (*ct != len_array(parsecmd)) ? *ct + 1 : *ct;
	}
	else
	{
		while (parsecmd[*ct])
		{
			if (!ft_strcmp(parsecmd[*ct], "&&"))
				break ;
			*ct = *ct + 1;
		}
		*ct = (*ct != len_array(parsecmd)) ? *ct + 1 : *ct;
	}
}

void	loop_binary_ope(t_all *all, char **parsecmd)
{
	int		ct;

	ct = 0;
	if (!check_good_bin_format(parsecmd))
		return ;
	while (parsecmd[ct])
	{
		goto_next_command(parsecmd, &ct, all->err_exec);
		if (ct == len_array(parsecmd))
			break ;
		if (!parsecmd[ct] || !parsecmd[ct][0])
			;
		else
		{
			if (check_redirection(parsecmd[ct]) == 1)
				exec_redirection_cmd(all, parsecmd[ct]);
			else
				exec_simple_cmd(all, parsecmd[ct]);
		}
		ct++;
	}
}
