/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 20:27:59 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 14:29:34 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned int	i;
	void			*memory;
	char			*current;

	i = 0;
	memory = (void *)malloc(sizeof(char *) * size);
	current = (char *)memory;
	if (memory == NULL)
		return (NULL);
	else
	{
		while (i++ < size)
		{
			current[i] = 0;
		}
	}
	return (memory);
}
