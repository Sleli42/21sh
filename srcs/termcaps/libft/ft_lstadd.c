/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 15:33:40 by lubaujar          #+#    #+#             */
/*   Updated: 2014/12/10 00:37:41 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, char *str)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return ;
	new->next = NULL;
	new->content = ft_strdup(str);
	if (*alst == NULL)
		*alst = new;
	if (*alst)
	{
		new->next = *alst;
		*alst = new;
	}
}
