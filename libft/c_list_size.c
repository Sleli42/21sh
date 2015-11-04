/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_list_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/31 20:57:16 by lubaujar          #+#    #+#             */
/*   Updated: 2015/07/31 21:12:17 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	c_list_size(t_circular *lst)
{
	t_circular	*tmp;
	int			ret;

	tmp = lst->next;
	ret = 0;
	if (tmp == lst)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		ret++;
		if (tmp == lst)
			return (ret);
	}
	return (ret);
}
