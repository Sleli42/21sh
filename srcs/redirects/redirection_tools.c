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

/*

int main()
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"grep", "pipe", NULL};
  char *wc[] = {"wc", NULL};
  char **cmd[] = {ls, grep, wc, NULL};

  loop_pipe(cmd);
  return (0);
}

void    loop_pipe(char ***cmd) 
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]);
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
          wait(NULL);
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          cmd++;
        }
    }
}

*/

void	dup_and_exec(t_all *all, char **cmd_argv, int fd2back, int fd2dup)
{
	dup2(all->fd2open, fd2dup);
	close(all->fd2open);
	exec_right_binary(all, cmd_argv);
	dup2(fd2back, fd2dup);
	close(fd2back);
	del_array(&cmd_argv);
}

void	display_array(char **array)
{
	if (array && *array)
	{
		while (*array)
		{
			printf("[ %s ]\n", *array);
			array++;
		}
	}
}

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
		if (ret)
			break ;
		if (tmp[i] == '|')
			ret = ft_strdup("|");
		else if (tmp[i] == '>')
		{
			if (tmp[i + 1] == '>')
				ret = ft_strdup(">>");
			else
				ret = ft_strdup(">");
		}
		else if (tmp[i] == '<')
		{
			if (tmp[i + 1] == '<')
				ret = ft_strdup("<<");
			else
				ret = ft_strdup("<");
		}
		i++;
	}
	return (ret);
}