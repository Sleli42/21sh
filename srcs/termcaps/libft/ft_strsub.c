/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 09:24:59 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 15:02:11 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	counter;

	if (s == NULL)
		return (NULL);
	dest = ft_strnew(len + 1);
	counter = 0;
	if (dest == NULL)
		return (NULL);
	while (counter < len + start)
	{
		if (counter >= start)
			dest[counter - start] = s[counter];
		counter++;
	}
	return (dest);
}
