/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhatir <skhatir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 15:46:53 by skhatir           #+#    #+#             */
/*   Updated: 2016/02/02 19:55:04 by skhatir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# define RD_OP			"-ersutpand"
# define DB(x, y)		((0x1 << x) | y)
# define S_ERR			"read [-ers] [-u fd] [-t timeout] [-p prompt]\
						 [-a array] [-n nchars] [-d delim] [name ...]\n"

typedef struct			s_read
{
	char				delim;
	int					opt;
	int					timeout;
	size_t				nchars;
}						t_read;

// typedef struct			s_var
// {
// 	char				*var_name;
// 	char				*content;
// 	struct s_var		*prev;
// 	struct s_var		*next;
// }						t_var;

// t_var					*local_var;
// int						query;
// size_t					max_len;

#endif
