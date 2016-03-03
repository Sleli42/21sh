# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/12 19:50:41 by lubaujar          #+#    #+#              #
#    Updated: 2016/03/03 15:44:14 by lubaujar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC = ft_atoi.c\
	  ft_bzero.c\
	  ft_epur_str.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_islower.c\
	  ft_isprint.c\
	  ft_isspace.c\
	  ft_isupper.c\
	  ft_iswhite.c\
	  ft_itoa.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_realloc.c\
	  ft_strrev.c\
	  ft_atoi_long.c\
	  ft_itoa_long.c\
	  ft_uitoa_long.c\
	  ft_uitoa.c\
	  ft_rand_a_b.c\
	  ft_intlen.c\
	  ft_tablen.c\
	  del_array.c\
	  lst_len.c\
	  get_next_line.c\

OBJ = $(SRC:.c=.o)

INC = -I./include/

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(INC) -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) *.o

fclean: clean
	@$(RM) $(NAME)

re: fclean all

exec:
	@gcc *.c -g $(FLAGS) -I./includes/
	@./a.out

.PHONY: all clean fclean re exec
