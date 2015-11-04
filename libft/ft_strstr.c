/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 17:13:18 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/08 18:02:45 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *s1, char const *s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(s2);
	if (len == 0)
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		while (s2[j] == s1[i + j])
		{
			if (j == len - 1)
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (0);
}
