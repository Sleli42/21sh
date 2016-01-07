# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/03 15:54:43 by lubaujar          #+#    #+#              #
#    Updated: 2015/12/16 14:22:04 by lubaujar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC				= srcs/
SRCS_ARROWS		= $(SRC)arrows_and_movements/
SRCS_BUILTINS	= $(SRC)builtins/
SRCS_ENV		= $(SRC)env/
SRCS_EXEC		= $(SRC)exec_binary/
SRCS_HISTORY 	= $(SRC)history/
SRCS_LISTS 		= $(SRC)lists/
SRCS_REDIRECTS 	= $(SRC)redirects/
SRCS_SHELL 		= $(SRC)shell/
SRCS_TERMCAPS 	= $(SRC)termcaps/

SRCS			= $(SRC)main.c \
			$(SRCS_ARROWS)horizontal_movements.c \
			$(SRCS_ARROWS)horizontal_movements_tools.c \
			$(SRCS_ARROWS)delete_char.c \
			$(SRCS_ARROWS)parse_keys.c \
			$(SRCS_ARROWS)clear_screen.c \
			$(SRCS_ARROWS)copy_cut_and_paste.c \
			$(SRCS_ARROWS)copy_tools.c \
			$(SRCS_ARROWS)cut_tools.c \
			$(SRCS_ARROWS)shift.c \
			$(SRCS_BUILTINS)builtins.c \
			$(SRCS_BUILTINS)builtins_tools.c \
			$(SRCS_ENV)env.c \
			$(SRCS_ENV)env_init.c \
			$(SRCS_ENV)env_tools.c \
	 		$(SRCS_EXEC)binary_tools.c \
			$(SRCS_EXEC)cmd_parse.c \
			$(SRCS_EXEC)cmd_exec.c \
		 	$(SRCS_HISTORY)history.c \
		 	$(SRCS_LISTS)clist.c \
			$(SRCS_LISTS)dlist.c \
			$(SRCS_LISTS)dlist_tools.c \
			$(SRCS_LISTS)dlist_2.c \
			$(SRCS_LISTS)dlist_2_tools.c \
			$(SRCS_REDIRECTS)pipe.c \
			$(SRCS_REDIRECTS)pipe_tools.c \
			$(SRCS_REDIRECTS)redirection.c \
			$(SRCS_REDIRECTS)redirection_tools.c \
		 	$(SRCS_SHELL)debug.c \
			$(SRCS_SHELL)error.c \
			$(SRCS_SHELL)shell_init.c \
			$(SRCS_SHELL)shell_loop.c \
			$(SRCS_SHELL)shell_tools.c \
			$(SRCS_TERMCAPS)termcaps_init.c \
			$(SRCS_TERMCAPS)termcaps_tools.c \
		
NAME = 21sh
RM = rm -rf
FLAGS = -Wall -Wextra -Werror
DEBUG = -g -gmodules -fexceptions -ftrapv -fcommon
LDFLAGS = -I./includes/ -I./libft/include/
LIB = libft/libft.a

OBJ = $(SRCS:.c=.o)

all:		$(NAME)

$(LIB):
			@make -C libft/

$(NAME):	$(LIB) $(OBJ)
	@gcc -o $(NAME) $(FLAGS) *.o -L./libft/ -lft -ltermcap
	@mkdir -p ./objs/
	@mv *.o ./objs/
	@echo "\n\t\t\033[35mexec \033[0m./$(NAME)"

%.o: %.c
	@echo "\033[35m[ GCC ] \033[0m$^"
	@gcc -c $^ -I./includes/ -I./libft/include $(FLAGS)

clean:
	@echo "\033[35m[ DELETE ]\033[0m *.o"
	@$(RM) *.o

fclean: clean
	@make fclean -C libft/
	@echo "\033[35m[ DELETE ]\033[0m ./21sh"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re