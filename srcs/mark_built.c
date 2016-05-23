/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:27:36 by skhatir           #+#    #+#             */
/*   Updated: 2016/05/23 16:53:43 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void			by_index(t_all *all, t_mark m_box, char *cmd)
{
	m_box.p_cmd = m_box.params > 1 ? first_cmd(cmd + 1) : cmd + 1;
	if ((size_t)(m_box.p_index = get_index(m_box.p_cmd)) > ft_tablen(m_box.history))
		return(ft_putendl("42sh: no event found"));
	m_box.p_cmd = m_box.p_index <= all->index_history && \
										m_box.p_index >= 0 ? \
		ft_strdup(obtain_history_p(m_box.history[m_box.p_index])) : NULL;
	if (!m_box.p_cmd)
		return ;
	m_box.p_cmd[ft_strlen(m_box.p_cmd)] = 0;
	if (m_box.params > 1)
		join_params(&m_box.p_cmd, cmd);
	realloc_termcaps_cmd(all, m_box.p_cmd);
	all->p_mark = m_box.params > 1 ? NULL : all->cmd_termcaps;
	all->cmd = m_box.p_cmd;
	return (m_box.params > 1 ? create_and_exec_command(all) : loop(all));
}

void			by_match(t_all *all, t_mark m_box, char *cmd)
{
	m_box.p_cmd = ft_strdup(obtain_history_p(m_box.history[m_box.p_index]));
	m_box.p_cmd[ft_strlen(m_box.p_cmd)] = 0;
	if (m_box.params > 1)
		join_params(&m_box.p_cmd, cmd);
	realloc_termcaps_cmd(all, m_box.p_cmd);
	all->p_mark = m_box.params > 1 ? NULL : all->cmd_termcaps;
	all->cmd = m_box.p_cmd;
	return (m_box.params > 1 ? create_and_exec_command(all) : loop(all));
}


void			built_mark(t_all *all, char *cmd)
{
	t_mark		m_box;

	(void)all;
	(void)cmd;
	all->p_mark = NULL;
	m_box.p_index = all->index_history > 0 ? all->index_history -1: 0;
	if (!ft_isalnum(*(cmd + 1)))
		return ;
	m_box.params = get_arg(cmd);
	if (!(m_box.p_cmd = m_box.params > 1 ? first_cmd(cmd + 1) : cmd + 1))
		return ;
	if (!(m_box.history = parse_history(all)))
		return (ft_putstr("NO HISTORY\n"));
	if (ft_isdigit((*m_box.p_cmd)))
		return (by_index(all, m_box, cmd));
	while (m_box.p_index >= 0)
	{
		if (*m_box.p_cmd && _M && \
										!ft_strncmp(m_box.p_cmd, \
				obtain_history_p(m_box.history[m_box.p_index]), \
											ft_strlen(m_box.p_cmd)))
			return (by_match(all, m_box, cmd));
		m_box.p_index--;
	}
	return (ft_putendl("42sh: event not found"));
}
