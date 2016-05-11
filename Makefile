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

# SRC					= srcs/
SRCS_ARROWS			= arrows_and_movements/
SRCS_AUTOCOMPLETE	= autocomplete/
SRCS_BUILTINS		= builtins/
SRCS_ENV			= env/
SRCS_EXEC			= exec_binary/
SRCS_HISTORY 		= history/
SRCS_LISTS 			= lists/
SRCS_REDIRECTS 		= redirects/
SRCS_SHELL 			= shell/
SRCS_TERMCAPS 		= termcaps/

SRC			= main.c \
			horizontal_movements.c \
			horizontal_movements_tools.c \
			goto_funcs.c \
			vertical_movements.c \
			delete_char.c \
			parse_keys.c \
			clear_screen.c \
			copy_cut_and_paste.c \
			copy_left.c \
			copy_right.c \
			copy_tools.c \
			cut_tools.c \
			shift.c \
			autocomplete.c \
			autocomplete_tools.c \
			binary_search.c \
			directory_search.c \
			equality_search.c \
			equality_search_tools.c \
			builtins.c \
			builtins_tools.c \
			read_built.c \
			read_built2.c \
			read_list.c \
			read_table_f.c \
			read_table_f2.c \
			reading.c \
			read_array.c \
			read_msc.c \
			local_var.c \
			local_var_msc.c \
			echo.c \
			mark_built.c \
			mark_built2.c \
			env.c \
			env_init.c \
			env_tools.c \
			env_tools_2.c \
			binary.c \
	 		binary_tools.c \
			parse_cmd.c \
			cmd_exec.c \
			hash.c \
		 	history.c \
		 	history_tools.c \
		 	clist.c \
			dlist.c \
			dlist_tools.c \
			dlist_2.c \
			dlist_2_tools.c \
			dlist_2_tools_2.c \
			pipe.c \
			pipe_tools.c \
			pipe_tools_2.c \
			redirection.c \
			redirection_tools.c \
			redirection_error.c \
			aggregation1.c \
			aggregation2.c \
			aggregation3.c \
			aggregation_tools.c \
			aggregation_error.c \
			error.c \
			shell_init.c \
			shell_loop.c \
			shell_loop_tools.c \
			shell_loop_tools_2.c \
			shell_tools.c \
			termcaps_init.c \
			termcaps_tools.c \
			binary_operators.c

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
	@echo "\t\t\033[35mexec \033[0m./$(NAME)"

$(OBJS): $(SRCS)
	@make -C libft/
	@gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	@echo "\033[35m[ GCC ] \033[0m   *.c"
	@mkdir -p $(OBJDIR)
	@mv $(OBJ) $(OBJDIR)

clean:
	@echo "\033[35m[ DELETE ]\033[0m *.o"
	@$(RM) $(OBJ)
	@$(RM) ./objs/

fclean: clean
	@make fclean -C libft/
	@echo "\033[35m[ DELETE ]\033[0m ./21sh"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re