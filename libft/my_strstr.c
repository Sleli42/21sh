/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 23:30:44 by lubaujar          #+#    #+#             */
/*   Updated: 2015/08/29 05:06:54 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_strstr(char *s)
{
	char	*tmp;
	int		i;

	tmp = s;
	i = 0;
	while (tmp[i])
	{
		// (s[i] == '>' && s[i + 1] == ' ') ? return(ft_strdup(">") : return(NULL));
		if (tmp[i] == '>')
		{
			if (tmp[i + 1] == '>' && tmp[i + 2] == ' ')
				return (">>");
			else
				return (">");
		}
		else if (tmp[i] == '<')
		{
			if (tmp[i + 1] == '<' && tmp[i + 2] == ' ')
				return ("<<");
			else
				return ("<");
		}
		else if (tmp[i] == '|')
			return ("|");
		i++;
	}
	return (NULL);
}
