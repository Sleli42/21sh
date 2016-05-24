/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_operators_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:01:01 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/24 14:01:03 by lubaujar         ###   ########.fr       */
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

int		check_good_bin_format(char **cmd)
{
	int		ct;

	ct = 0;
	if (!ft_strcmp(cmd[0], "&&") || !ft_strcmp(cmd[0], "||"))
		return (error_bin_operators(cmd[0]));
	while (cmd[ct])
	{
		if (cmd[ct] == NULL)
			return (error_bin_operators(cmd[len_array(cmd) - 1]));
		else if (!ft_strcmp(cmd[ct], "||") || !ft_strcmp(cmd[ct], "&&"))
		{
			if (cmd[ct - 1] == NULL || cmd[ct + 1] == NULL)
				return (error_bin_operators(cmd[ct]));
		}
		else if ((!ft_strncmp(cmd[ct], "&&", 2) && ft_strlen(cmd[ct]) > 2)
			|| (!ft_strncmp(cmd[ct], "||", 2) && ft_strlen(cmd[ct]) > 2))
			return (error_bin_operators(cmd[ct] + 2));
		else if ((!ft_strncmp(cmd[ct], "&&", 2) || \
							!ft_strncmp(cmd[ct], "||", 2))
			&& ((!ft_strncmp(cmd[ct + 1], "&&", 2) || \
							!ft_strncmp(cmd[ct + 1], "||", 2))))
			return (error_bin_operators(cmd[ct + 1]));
		ct++;
	}
	return (1);
}

void	goto_next_command(char **parsecmd, int *ct, int err)
{
	if (!ft_strcmp(parsecmd[*ct], "&&"))
		and_operator(parsecmd, ct, err);
	else if (!ft_strcmp(parsecmd[*ct], "||"))
		or_operator(parsecmd, ct, err);
}
