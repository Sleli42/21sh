/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 10:59:23 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/17 22:28:07 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*cpy;

	new = (t_list *)ft_memalloc(sizeof(content_size));
	if (new == NULL)
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		cpy = ft_memalloc(content_size);
		if (cpy == NULL)
			return (NULL);
		new->content = ft_memcpy(cpy, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
