# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubaujar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/03 15:54:43 by lubaujar          #+#    #+#              #
#    Updated: 2015/11/03 15:54:44 by lubaujar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
RM = rm -rf
FLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -I./includes/ -I./libft/include/

SRC = binary_tools.c \
		builtins.c \
		cmd_exec.c \
		cmd_parse.c \
		dlist.c \
		dlist_2.c \
		clist.c \
		env.c \
		error.c \
		init.c \
		main.c \
		pipe.c \
		redirection.c \
		tools.c \
		termcaps.c \
		history.c \
		moves.c \
		autocomplete.c


OBJ = $(SRC:.c=.o)

	SRCDIR	= ./srcs/
	OBJDIR	= ./objs/
	INCDIR	= ./includes/
	SRCS	= $(addprefix $(SRCDIR), $(SRC))
	OBJS	= $(addprefix $(OBJDIR), $(OBJ))
	INCS	= $(addprefix $(INCDIR), $(INC))

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	@gcc $(FLAGS) -o $@ $^ -L./libft/ -lft -ltermcap
	@echo "\\033[1;34m\tPlease wait ...\\033[0;39m"
	@echo "\\033[1;34m\t\texec ./21sh\\033[0;39m"

$(OBJS): $(SRCS)
	@make -C libft/
	@gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	@mkdir -p $(OBJDIR)
	@mv $(OBJ) $(OBJDIR)

clean:
	@echo "\nRM *.o.. \t\033[35m[ DELETE ]\033[0m"
	@$(RM) $(OBJS)
	@$(RM) *.o

fclean: clean
	@make fclean -C libft/
	@echo "RM ./21sh..\t\033[35m[ DELETE ]\033[0m"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re