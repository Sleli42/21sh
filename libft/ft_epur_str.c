/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/26 22:05:55 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/28 07:30:14 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_epur_str(char *s)
{
	char	*ret;
	int		j;

	j = 0;
	ret = ft_strnew(ft_strlen(s) + 1);
	if ((!s && !*s) || !ret)
		return (NULL);
	while ((*s && *s == ' ') || (*s && *s == '\t'))
		s++;
	while (*s)
	{
		ret[j++] = *(s++);
		if (*s == ' ' || *s == '\t')
		{
			while ((*s && *s == ' ') || (*s && *s == '\t'))
				s++;
			if (*s != 0)
				ret[j++] = ' ';
			else
				break ;
		}
	}
	ret[j] = '\0';
	return (ret);
}
