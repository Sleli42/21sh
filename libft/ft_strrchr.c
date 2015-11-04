/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 15:28:22 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 14:35:23 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	unsigned int	i;
	char			ch;

	i = ft_strlen(s);
	ch = c;
	while (s[i] != ch)
	{
		if (s[i] == s[0])
			return (0);
		i--;
	}
	return ((char *)s + i);
}
