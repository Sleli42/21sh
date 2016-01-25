/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 20:07:50 by lubaujar          #+#    #+#             */
/*   Updated: 2016/01/25 20:07:51 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

#ifndef COLORS_H
# define COLORS_H

# define RED				"\e[31m"
# define BLUE 				"\e[34m"
# define CYAN  				"\e[36m"
# define BLACK 				"\e[30m"
# define GREEN  			"\e[32m"
# define BROWN				"\e[0;33m"
# define DEFAULT 			"\e[39m"
# define MAGENTA 			"\e[35m"
# define BOLD_RED  			"\e[1;31m"
# define BOLD_BLUE  		"\e[1;34m"
# define BOLD_CYAN  		"\e[1;36m"
# define LIGHT_GREY 		"\e[37m"
# define BOLD_BLACK 		"\e[1;30m"
# define BOLD_GREEN  		"\e[1;32m"
# define BOLD_BROWN			"\e[0;1;33m"
# define BOLD_DEFAULT 		"\e[1;39m"
# define BOLD_MAGENTA 		"\e[1;35m"
# define BOLD_LIGHT_GREY 	"\e[1;37m"
# define END				"\033[0m"

#endif