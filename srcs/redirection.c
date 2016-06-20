/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:23:54 by lubaujar          #+#    #+#             */
/*   Updated: 2016/03/21 16:03:23 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	display_array(char **array)
{
	int	ct;
	char	**tmp;

	tmp = array;
	ct = 0;
	while (tmp[ct])
	{
		ft_putendl(tmp[ct]);
		ct++;
	}
}

char	**replace_argv(char **array, char *redir)
{
	char	**ret;
	int	ct;
	int	ct2;

	ct = 0;
	ct2 = 1;
	if (!array || !(ret = (char **)malloc(sizeof(char *) * \
		len_array(array) + 1)))
		return (NULL);
	while (array[ct2])
	{
		if (!ft_strcmp(array[ct2 - 1], redir))
			break ;
		ct2++;
	}
	ct2 += 1;
	while (array[ct2])
		ret[ct++] = ft_strdup(array[ct2++]);
	ct2 = 0;
	while (array[ct2] && ct < len_array(array))
		ret[ct++] = ft_strdup(array[ct2++]);
	ret[ct] = NULL;
	return (ret);
}

int		count_args(char **array, char *redir)
{
	int		ret;
	int		ct;

	ret = 0;
	ct = 0;
	while (array[ct])
	{
		if (!ft_strcmp(array[ct], redir))
			break ;
		ct++;
		ret++;
	}
	return (ret);
}

char	**rework_args_2_exec(char **array, char *redir)
{
	int		ct;
	int		stop;
	char	**ret;

	ct = 0;
	stop = count_args(array, redir);
	if (!(ret = (char **)malloc(sizeof(char *) * stop + 1)))
		return (NULL);
	while (array[ct] && ct < stop)
	{
		ret[ct] = ft_strdup(array[ct]);
		ct++;
	}
	ret[ct] = NULL;
	return (ret);
}

char	*formatting_redirect_cmd(char *cmd, char *redir)
{
	int		ct;
	int		ct2;
	char	*ret;

	ct = 0;
	ct2 = 0;
	ret = ft_strnew(ft_strlen(cmd) + 20);
	while (cmd[ct])
	{
		if (cmd[ct] == redir[0] && cmd[ct + 1] != ' ' && cmd[ct + 1] != redir[0])
		{
			ret[ct2++] = cmd[ct++];
			ret[ct2++] = ' ';
		}
		else
			ret[ct2++] = cmd[ct++];
	}
	ret[ct2] = 0;
	ft_strdel(&cmd);
	return (ret);
}

static int		check_if_valid_cmd(t_all *all, char *try)
{
	int		ct;
	char	*bin_tmp;

	ct = 0;
	bin_tmp = NULL;
	while (all->path2exec[ct])
	{
		if (!(bin_tmp = create_path(all->path2exec[ct], try)))
		{
			write_error_exec(try);
			return (0);
		}
		if (bin_tmp && good_access(bin_tmp))
			break ;
		bin_tmp ? ft_strdel(&bin_tmp) : NULL;
		ct++;
	}
	if (!all->path2exec[ct])
	{
		all->err = 1;
		write_error(try);
		return (0);
	}
	return (1);
}

static int		check_error(t_all *all, char **array, char *redir)
{
	char	**tmp;
	int		ct;

	ct = 0;
	tmp = array;
	if ((len_array(array) == 1) || (array[1][0] == '&' && !array[1][1]))
		return (redirection_error_2());
	else if (!ft_strcmp(tmp[0], redir) && len_array(array) == 2)
		return (redirection_error_4());
	if (!check_if_valid_cmd(all, tmp[0]))
		return (-1);
	while (tmp[ct])
	{
		if (!ft_strcmp(tmp[ct], redir))
		{
			if (!tmp[ct + 1])
				return (redirection_error_2());
			else if (ct == 0)
				return (redirection_error_4());
		}
		ct++;
	}
	return (1);
}

void	erase_and_replace(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		cmd = formatting_redirect_cmd(cmd, ">");
		redirect = ft_strsplit(cmd, ' ');
		if (len_array(redirect) > 1 && redirect[0][0] == '>')
			redirect = replace_argv(redirect, ">");
		if (!check_error(all, redirect, ">"))
			return ;
		argv = rework_args_2_exec(redirect, ">");
		if ((all->fd2open = open(redirect[len_array(redirect) - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return (redirection_error(redirect[len_array(redirect) - 1]));
		dupstdout = dup(1);
		(!all->err) ? dup_and_exec(all, argv, dupstdout, 1) : NULL;
		redirect ? del_array(&redirect) : NULL;
	}
}

void	add_to_end(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;

	argv = NULL;
	redirect = NULL;
	cmd = formatting_redirect_cmd(cmd, ">>");
	redirect = ft_strsplit(cmd, ' ');
	if (len_array(redirect) > 1 && redirect[0][0] == '>')
		redirect = replace_argv(redirect, ">>");
	if (!check_error(all, redirect, ">>"))
		return ;
	argv = rework_args_2_exec(redirect, ">>");
	if ((all->fd2open = open(redirect[len_array(redirect) - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return (redirection_error(redirect[len_array(redirect) - 1]));
	dupstdout = dup(1);
	(!all->err) ? dup_and_exec(all, argv, dupstdout, 1) : NULL;
	redirect ? del_array(&redirect) : NULL;
}

int		check_double_redirection(char **array)
{
	char	**tmp;
	int		ct;
	int		stop;

	tmp = array;
	ct = 0;
	stop = 0;
	while (tmp[ct])
	{
		if ((tmp[ct][0] == '<' && !stop)
			|| (tmp[ct][0] == '>' && !stop))
			stop += 1;
		else if ((tmp[ct][0] == '>' && stop)
			|| (tmp[ct][0] == '<' && stop))
			stop += 1;
		ct++;
	}
	if (stop == 2)
		return (1);
	return (0);
}

char	*first_redirect(char **array)
{
	char	**tmp;
	int		ct;

	tmp = array;
	ct = 0;
	while (tmp[ct])
	{
		if (tmp[ct][0] == '>' || tmp[ct][0] == '<')
			return (tmp[ct]);
		ct++;
	}
	return (NULL);
}

char	*get_fd_2_open(char **array, char *redir)
{
	char	**tmp;
	int		ct;

	tmp = array;
	ct = 0;
	while (tmp[ct])
	{
		// printf("tmp[ct]: [ %s ]\n", tmp[ct]);
		if (tmp[ct][0] == redir[0])
		{
			// printf("found: [ %s ]\n&& +1: [ %s ]\n", tmp[ct], tmp[ct + 1]);
			return (tmp[ct + 1]);
		}
		ct++;
	}
	return (NULL);
}

void	exec_double_redirection(t_all *all, char **array)
{
	char	**argv;
	int		fd;
	int		dupstdin;
	int		dupstdout;

	argv = rework_args_2_exec(array, first_redirect(array));
	if ((all->fd2open = open(get_fd_2_open(array, "<"), \
		O_RDONLY, 0644)) == -1)
		return (redirection_error(get_fd_2_open(array, "<")));
	if ((fd = open(get_fd_2_open(array, ">"), \
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (redirection_error(get_fd_2_open(array, ">")));
	dupstdin = dup(0);
	dupstdout = dup(1);
	dup2(fd, 1);
	(!all->err) ? dup_and_exec(all, argv, dupstdin, 0) : NULL;
	close(fd);
	dup2(dupstdout, 1);
	close(dupstdout);
	array ? del_array(&array) : NULL;
}

void	read_file(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdin;

	argv = NULL;
	redirect = NULL;
	if (check_aggregations(cmd))
		exec_aggregations(all, cmd);
	else
	{
		cmd = formatting_redirect_cmd(cmd, "<");
		redirect = ft_strsplit(cmd, ' ');
		if (len_array(redirect) > 1 && redirect[0][0] == '<')
			redirect = replace_argv(redirect, "<");
		if (!check_error(all, redirect, "<"))
			return ;
		if (check_double_redirection(redirect))
			return (exec_double_redirection(all, redirect));
		argv = rework_args_2_exec(redirect, "<");
		if ((all->fd2open = open(redirect[len_array(redirect) - 1], \
			O_RDONLY, 0644)) == -1)
			return (redirection_error(redirect[len_array(redirect) - 1]));
		dupstdin = dup(0);
		(!all->err) ? dup_and_exec(all, argv, dupstdin, 0) : NULL;
		redirect ? del_array(&redirect) : NULL;
	}
}

int		count_redirect(char *s)
{
	int		ct;
	int		ret;

	ct = 0;
	ret = 0;
	if (!s)
		return (0);
	while (s[ct])
	{
		if (s[ct] == '<')
		{
			while (s[ct] == '<')
			{
				ret++;
				if (ret > 2)
					return (ret);
				ct++;
			}
			ret = 0;
		}
		ct++;
	}
	return (ret);
}

void	read_stdin(t_all *all, char *cmd)
{
	char	**redirect;
	char	**argv;
	char	*tmp_buff;

	cmd = formatting_redirect_cmd(cmd, "<<");
	redirect = ft_strsplit(cmd, ' ');
	if (len_array(redirect) > 1 && redirect[0][0] == '<')
		redirect = replace_argv(redirect, "<<");
	if (!check_error(all, redirect, "<<"))
		return ;
	argv = NULL;
	if ((all->fd2open = open(".tmp_file", \
		O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		error("OPEN");
	argv = rework_args_2_exec(redirect, "<<");
	// display_array(argv);
	while (1)
	{
		ft_putstr("> ");
		tmp_buff = read_stdin_cpy_buff();
		if (ft_strcmp(tmp_buff, redirect[len_array(redirect) - 1]))
		{
			ft_putstr_fd(tmp_buff, all->fd2open);
			ft_putstr_fd("\n", all->fd2open);
		}
		if (read_stdin_cmp_key(all, argv, \
			redirect[len_array(redirect) - 1], tmp_buff))
			break ;
		write(1, "\n", 1);
	}
	redirect ? del_array(&redirect) : NULL;
}
