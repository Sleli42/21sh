/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 17:23:54 by lubaujar          #+#    #+#             */
/*   Updated: 2015/11/04 17:23:55 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	dup_and_exec(char **argv, int fd2open, int fd2back, int fd2dup)
{
	dup2(fd2open, fd2dup);
	close(fd2open);
	execve(argv[0], argv, NULL);
	//exec_right_binary(all, argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
	del_array(&argv);
}

void	erase_and_replace(char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;
	int		fd2open;

	argv = NULL;
	redirect = ft_strsplit(cmd, '>');
	redirect[1] = ft_epur_str(redirect[1 + 1]);
	if ((fd2open = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		write(1, "err0r\n", 6);//shell_error("OPEN", redirect[1]);
	argv = ft_strsplit(redirect[0], ' ');
	dupstdout = dup(STDOUT_FILENO);
	del_array(&redirect);
	dup_and_exec(argv, fd2open, dupstdout, STDOUT_FILENO);
}

void	add_to_end(char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdout;
	int		fd2open;

	argv = NULL;
	redirect = ft_strsplit(cmd, '>');
	redirect[1] = ft_epur_str(redirect[1 + 1]);
	if ((fd2open = open(redirect[1], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		write(1, "err0r\n", 6);//shell_error("OPEN", redirect[1]);
	argv = ft_strsplit(redirect[0], ' ');
	dupstdout = dup(STDOUT_FILENO);
	del_array(&redirect);
	dup_and_exec(argv, fd2open, dupstdout, STDOUT_FILENO);
}

void	read_file(char *cmd)
{
	char	**redirect;
	char	**argv;
	int		dupstdin;
	int		fd2open;

	argv = NULL;
	redirect = ft_strsplit(cmd, '>');
	redirect[1] = ft_epur_str(redirect[1 + 2]);
	if ((fd2open = open(redirect[1], O_RDONLY)) == -1)
		write(1, "err0r\n", 6);//shell_error("OPEN", redirect[1]);
	argv = ft_strsplit(redirect[0], ' ');
	dupstdin = dup(STDIN_FILENO);
	del_array(&redirect);
	dup_and_exec(argv, fd2open, dupstdin, STDIN_FILENO);
}

void	read_stdin(char *cmd)
{
	char	**redirect;
	char	**argv;
	char	*key;
	char	*buff;
	int		dupstdin;

	argv = NULL;
	buff = NULL;
	redirect = ft_strsplit(cmd, '<');
	key = ft_epur_str(redirect[1 + 2]);
	argv = ft_strsplit(redirect[0], ' ');
	while (1)
	{
		ft_putstr("heredoc> ");
		get_next_line(0, &buff);
		if (ft_strcmp(key, buff) == 0)
		{
			dupstdin = dup(0);
			dup_and_exec(argv, STDIN_FILENO, dupstdin, STDIN_FILENO);
			break ;
		}
		else
			if (buff != NULL)
				ft_strdel(&buff);
	}
	del_array(&redirect);
}