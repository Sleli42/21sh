/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 23:02:41 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/14 15:42:29 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	int	i;
	int	len;

	if (s != NULL && f != NULL)
	{
		i = 0;
		len = ft_strlen(s);
		while (i < len)
		{
			(*f)(s);
			i++;
			s++;
		}
	}
}
