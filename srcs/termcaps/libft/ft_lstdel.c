/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 13:58:06 by lubaujar          #+#    #+#             */
/*   Updated: 2014/11/17 22:27:03 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next_list;
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		next_list = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = next_list;
	}
	*alst = NULL;
}
