/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 23:10:56 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 14:31:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int				i;
	int				len;
	unsigned int	index;

	if (s != NULL && f != NULL)
	{
		i = 0;
		index = 0;
		len = ft_strlen(s);
		while (i < len)
		{
			(*f)(index, s);
			s++;
			i++;
			index++;
		}
	}
}
