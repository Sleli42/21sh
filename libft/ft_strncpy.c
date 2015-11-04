/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:57:35 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/07 17:21:30 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	unsigned int i;

	i = ft_strlen(src);
	if (i < n)
	{
		dest = ft_memcpy(dest, src, n);
		while (i < n)
		{
			dest[i] = 0;
			i++;
		}
	}
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}
