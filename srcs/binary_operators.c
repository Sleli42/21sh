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

int		error_bin_operators(char *err)
{
	ft_putstr("42sh: syntax error near unexpected token `");
	ft_putstr(err);
	ft_putstr("'\n");
	return (0);
}

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

int		check_good_bin_format(char **parsecmd)
{
	int		ct;

	ct = 0;
	if (!ft_strcmp(parsecmd[0], "&&") || !ft_strcmp(parsecmd[0], "||"))
		return (error_bin_operators(parsecmd[0]));
	while (parsecmd[ct])
	{
		if ((!ft_strncmp(parsecmd[ct], "&&", 2) && ft_strlen(parsecmd[ct]) > 2)
			|| (!ft_strncmp(parsecmd[ct], "||", 2) && ft_strlen(parsecmd[ct]) > 2))
			return (error_bin_operators(parsecmd[ct] + 2));
		if ((!ft_strncmp(parsecmd[ct], "&&", 2) || !ft_strncmp(parsecmd[ct], "||", 2))
			&& ((!ft_strncmp(parsecmd[ct + 1], "&&", 2) || \
				!ft_strncmp(parsecmd[ct + 1], "||", 2))))
			return (error_bin_operators(parsecmd[ct + 1]));
		ct++;
	}
	return (1);
}

// static void		display_array(char **array)
// {
// 	int		i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("\t\t [ %s ] \n", array[i]);
// 		i++;
// 	}
// }

void	loop_binary_ope(t_all *all, char **parsecmd, int bin_ope)
{
	int		ct;
	int		cmp;

	ct = 0;
	cmp = 0;
	if (!check_good_bin_format(parsecmd))
		return ;
	// display_array(parsecmd);
	while (parsecmd[ct])
	{
		if (all->err_exec == 256)
		{
			/* a faire */
		}
		if (!ft_strcmp(parsecmd[ct], "&&"))
		{
			/* a faire */
		}
		else if (!ft_strcmp(parsecmd[ct], "||"))
		{
			/* a faire */
		}
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
	if (cmp == bin_ope)
		ft_putstr("soooo gooood\n");
}
