/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 16:42:37 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/13 15:02:33 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_spaces(char const *s)
{
	size_t	i;

	i = 0;
	while (ft_iswhite(s[i]))
		i++;
	return (i);
}

static size_t	count_spaces_return(char const *s, size_t len)
{
	if (len)
	{
		len--;
		while (ft_iswhite(s[len]) && len > 0)
			len--;
	}
	return (len);
}

char			*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;

	if (s)
	{
		len = count_spaces_return(s, ft_strlen(s));
		start = count_spaces(s);
		if (!len && !start)
			return (ft_strdup(s));
		else if (start == ft_strlen(s))
			return (ft_strsub(s, 0, 0));
		else
			return (ft_strsub(s, start, len - start + 1));
	}
	return (NULL);
}
