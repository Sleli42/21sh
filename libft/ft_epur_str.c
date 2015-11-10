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
#include <stdio.h>

char	*ft_epur_str(char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(ret = (char *)malloc(sizeof(char) * 200)))
		return (NULL);
	while ((s[i] && s[i] == ' ') || (s[i] && s[i] == '\t'))
		i++;
	while (s[i])
	{
		ret[j++] = s[i++];
		if (s[i] == ' ' || s[i] == '\t')
		{
			while ((s[i] && s[i] == ' ') || (s[i] && s[i] == '\t'))
				i++;
			if (s[i + 1] != '\0')
				ret[j++] = ' ';
			else
				break ;
		}
	}
	ret[j] = '\0';
	return (ret);
}