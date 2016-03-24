/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_built2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:56:10 by skhatir           #+#    #+#             */
/*   Updated: 2016/03/21 16:08:23 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int						dft_reply(char ***cmd_tab)
{
	char				**dft_reply;

	dft_reply = NULL;
	if ((dft_reply = (char **)malloc(sizeof(char *) * 3)) == NULL)
		exit(printf("MALLOC dft_reply failed\n"));
	dft_reply[0] = ft_strdup("read");
	dft_reply[1] = ft_strdup("REPLY");
	dft_reply[2] = NULL;
	*cmd_tab ? ft_tabdel(cmd_tab) : NULL;
	(*cmd_tab) = dft_reply;
	return (0x0);
}

int						read_ct(char **cmd_tab, int *opt, t_all *all)
{
	int					i;
	int					j;
	int					ret;

	i = 0;
	ret = 0;
	while (cmd_tab[ret][++i])
	{
		j = 0;
		while (RD_OP[++j])
		{
			if (RD_OP[j] == cmd_tab[ret][i])
			{
				(*opt) = DB((j - 1), (*opt));
				if ((ret = j > 0x3 ? check_requiere(j, cmd_tab, i, all)\
										: 1) == 2)
					return (ret);
				break ;
			}
		}
		if (!RD_OP[j] || ret < 0)
			return (-1);
	}
	return (ret);
}
