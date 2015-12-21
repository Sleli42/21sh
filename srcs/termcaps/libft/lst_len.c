/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 18:48:30 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/11 22:58:58 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lst_len(t_list *lst)
{
	int		ret;
	t_list	*tmp;

	ret = 0;
	tmp = lst;
	if (tmp)
	{
		while (tmp)
		{
			ret++;
			tmp = tmp->next;
		}
	}
	return (ret);
}
