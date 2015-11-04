/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 15:19:04 by lubaujar          #+#    #+#             */
/*   Updated: 2015/05/22 18:35:38 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	char		*new;

	s1 = (s1 == NULL) ? "" : s1;
	s2 = (s2 == NULL) ? "" : s2;
	if (s1 && s2)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		new = ft_strnew(i);
		if (new)
		{
			new = ft_strcpy(new, s1);
			new = ft_strcat(new, s2);
			return (new);
		}
	}
	return (NULL);
}
