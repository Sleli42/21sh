/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 11:42:27 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:06:35 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

int			good_access(char *bin)
{
	if (access(bin, F_OK) == 0)
		if (access(bin, X_OK) == 0)
			return (1);
	return (0);
}

char		*get_pwd_path(char *bin)
{
	char	buf[512];
	char	*pwd;
	char	*tmp;

	if ((pwd = ft_strdup(getcwd(buf, 512))) == NULL)
		return (NULL);
	tmp = ft_strjoin(pwd, ++bin);
	return (tmp);
}

char		*create_path(char *path, char *bin)
{
	char	*tmp;
	char	*ret;

	if (*bin == '/')
		return (bin);
	else if (*bin == '.')
		return (get_pwd_path(bin));
	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, bin);
	tmp ? ft_strdel(&tmp) : NULL;
	return (ret);
}
