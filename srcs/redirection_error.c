/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:55:45 by lubaujar          #+#    #+#             */
/*   Updated: 2016/05/03 15:55:49 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "full_sh.h"

void	redirection_error(char *file)
{
	ft_putstr("42sh: no such file or directory: ");
	ft_putstr(file);
	ft_putchar('\n');
}

void	redirection_error_2(void)
{
	ft_putstr("42sh: Parse error: Syntax error\n");
	return ;
}

/*****************

wc -l < Makefile > file && wc -l < auteur >> file || ls -l ; cat file

medium split:

	[ wc -l < Makefile > file ]
		-> [ && ] <-
	[ wc -l < auteur >> file ]
		-> [ || ] <-
	[ ls -l ]

	[ cat ]
	[ file ]


	---------

	split:

					[ wc ]
					[ -l ]
			[ < ]
					[ Makefile ]
			[ > ]
					[ file ]

		[ && ]

					[ wc -l ]
			[ < ]
					[ auteur ]
			[ >> ]
					[ file ]

		[ || ]

					[ ls ]
					[ -l ]
	[ ; ]

					[ cat ]
					[ file ]

[lubaujar@e2r4p12 42sheu (master ✗)]$ &&
	zsh: parse error near `&&'
[lubaujar@e2r4p12 42sheu (master ✗)]$ &&&&
	zsh: parse error near `&&'
[lubaujar@e2r4p12 42sheu (master ✗)]$ ls -l &&& ls
	zsh: parse error near `&'

********************/