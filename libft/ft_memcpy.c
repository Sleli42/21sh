/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 19:09:19 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 14:33:23 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	char		*cast_dst;
	char const	*cast_src;

	cast_dst = (char *)dst;
	cast_src = (char const *)src;
	while (n > 0)
	{
		cast_dst[n - 1] = cast_src[n - 1];
		n--;
	}
	return (dst);
}
