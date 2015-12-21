/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 11:32:49 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/08 12:43:02 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t n)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char *) * n);
	tmp = ft_strncpy(tmp, src, n);
	dst = (void *)ft_strncpy(dst, tmp, n);
	free(tmp);
	return (dst);
}
