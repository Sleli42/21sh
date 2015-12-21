/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 23:17:36 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 14:31:57 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	str = ft_strnew(len);
	while (i < len)
	{
		str[i] = (*f)(s[i]);
		i++;
	}
	return (str);
}
