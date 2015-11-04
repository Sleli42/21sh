/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:26:18 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/05 19:18:27 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s1[size])
		size++;
	while (s2[i] && i < n)
	{
		s1[size] = s2[i];
		size++;
		i++;
	}
	s1[size] = '\0';
	return (s1);
}
