/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/03 23:43:01 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/03 23:43:02 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	dup_and_exec(t_all *all, char **cmd_argv, int fd2back, int fd2dup)
{
	dup2(all->fd2open, fd2dup);
	close(all->fd2open);
	exec_right_binary(all, cmd_argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
	del_array(&cmd_argv);
}

// void	display_array(char **array)
// {
// 	if (array && *array)
// 	{
// 		while (*array)
// 		{
// 			printf("[ %s ]\n", *array);
// 			array++;
// 		}
// 	}
// }

char	*my_strstr(t_all *all, char *s)
{
	char	*tmp;
	char	*ret;
	int		i;

	tmp = s;
	ret = NULL;
	i = 0;
	all->inpipe = 0;
	all->inredir = 0;
	while (tmp[i])
	{
		if (tmp[i] == '|')
			all->inpipe = 1;
		else if (tmp[i] == '>')
		{
			all->inredir = 1;
			if (tmp[i + 1] == '>')
				ret = ft_strdup(">>");
			else
				ret = ft_strdup(">");
			break ;
		}
		else if (tmp[i] == '<')
		{
			all->inredir = 1;
			if (tmp[i + 1] == '<')
				ret = ft_strdup("<<");
			else
				ret = ft_strdup("<");
			break ;
		}
		i++;
	}
	return (ret);
}