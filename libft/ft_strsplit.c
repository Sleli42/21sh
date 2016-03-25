/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:42:32 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/17 23:25:58 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				count_words(char *s, char c)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (s && s[i])
	{
		while (s[i])
		{
			if (s[i] == c)
			{
				if (s[i + 1] == '\0')
					break ;
				ret++;
			}
			i++;
		}
		ret = ret + 1;
	}
	return (ret);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		ct;
	int		stop;
	int		i;
	int		j;

	ct = -1;
	i = 0;
	if (s == NULL)
		return (NULL);
	stop = count_words((char *)s, c);
	if (!(array = (char **)malloc(sizeof(char *) * stop + 1)))
		return (NULL);
	while (++ct < stop)
	{
		j = 0;
		if (!(array[ct] = (char *)malloc(sizeof(char) * 4096)))
			return (NULL);
		while (s[i] && s[i] != c)
			array[ct][j++] = s[i++];
		array[ct][j] = '\0';
		i = i + 1;
	}
	array[ct] = NULL;
	return (array);
}
