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

NAME = 21sh
RM = rm -rf
FLAGS = -Wall -Wextra -Werror
DEBUG = -g -gmodules -fexceptions -ftrapv -fcommon
LDFLAGS = -I./includes/ -I./libft/include/

ARROWS = srcs/arrows_and_movements
BUILTINS = srcs/builtins
ENV = srcs/env
EXEC = srcs/exec_binary
HISTORY = srcs/history
LISTS = srcs/lists
REDIRECTS = srcs/redirects
SHELL = srcs/shell
TERMCAPS = srcs/termcaps

ARROWS =	$(ARROWS)/horizontal_movements.c \
			$(ARROWS)/horizontal_movemnts_tools.c \
			$(ARROWS)/delete_char.c \
			$(ARROWS)/parse_keys.c \
# AUTOCOMPLETE = autocomplete/autocomplete.c \
BUILTINS =		$(BUILTINS)/builtins.c \
		$(BUILTINS)/builtins_tools.c \

ENV =		$(ENV)/env.c \
		$(ENV)/env_init.c \
		$(ENV)/env_tools.c \

EXEC = 		$(EXEC)/binary_tools.c \
		$(EXEC)/cmd_parse.c \
		$(EXEC)/cmd_exec.c \

HISTORY = 		$(HISTORY)/history.c \

LISTS = 		$(LISTS)/clist.c \
		$(LISTS)/dlist.c \
		$(LISTS)/dlist_tools.c \
		$(LISTS)/dlist_2.c \
		$(LISTS)/dlist_2_tools.c \

REDIRECTS = 		$(REDIRECTS)/pipe.c \
		$(REDIRECTS)/pipe_tools.c \
		$(REDIRECTS)/redirection.c \
		$(REDIRECTS)/redirection_tools.c \

SHELL = 	$(SHELL)/debug.c \
		$(SHELL)/error.c \
		$(SHELL)/main.c \
		$(SHELL)/shell_init.c \
		$(SHELL)/shell_loop.c \
		$(SHELL)/shell_tools.c \

TERMCAPS =		$(TERMCAPS)termcaps_init.c \
		$(TERMCAPS)termcaps_tools.c
		
OBJ = 	$(ARROWS:.c=.o) \
		$(BUILTINS:.c=.o) \
		$(ENV:.c=.o) \
		$(EXEC:.c=.o) \
		$(HISTORY:.c=.o) \
		$(LISTS:.c=.o) \
		$(REDIRECTS:.c=.o) \
		$(SHELL:.c=.o) \
		$(TERMCAPS:.c=.o) \

	# SRCDIR	= ./srcs/
	# OBJDIR	= ./objs/
	# INCDIR	= ./includes/
	# SRCS	= $(addprefix $(SRCDIR), $(SRC))
	# OBJS	= $(addprefix $(OBJDIR), $(OBJ))
	# INCS	= $(addprefix $(INCDIR), $(INC))

$(NAME):	$(OBJ)
			@gcc $(FLAGS) -o $@ $^ -L./libft/ -lft -ltermcap

all: $(NAME)

clean:
			rm -rf $(OBJ)
fclean:		clean
			rm -f $(NAME)
re:			fclean

# $(NAME): $(OBJS) $(INCS)
# 	@gcc $(FLAGS) -o $@ $^ -L./libft/ -lft -ltermcap
# 	@echo "\\033[1;34m\tPlease wait ...\\033[0;39m"
# 	@echo "\\033[1;34m\t\texec ./21sh\\033[0;39m"

# $(OBJS): $(SRCS)
# 	@make -C libft/
# 	@gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
# 	@mkdir -p $(OBJDIR)
# 	@mv $(OBJ) $(OBJDIR)

# clean:
# 	@echo "\nRM *.o.. \t\033[35m[ DELETE ]\033[0m"
# 	@$(RM) $(OBJS)
# 	@$(RM) *.o

# fclean: clean
# 	@make fclean -C libft/
# 	@echo "RM ./21sh..\t\033[35m[ DELETE ]\033[0m"
# 	@$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
