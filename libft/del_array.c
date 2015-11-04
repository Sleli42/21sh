/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 16:27:54 by lubaujar          #+#    #+#             */
/*   Updated: 2015/06/05 16:46:20 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_array(char ***array)
{
	int		i;
	char	**tmp;

	tmp = *array;
	i = 0;
	if (tmp)
	{
		while (tmp && tmp[i])
		{
			ft_strdel(&tmp[i]);
			i++;
		}
		free(tmp);
		tmp = NULL;
	}
}
