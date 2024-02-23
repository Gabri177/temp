# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 21:42:20 by yugao             #+#    #+#              #
#    Updated: 2024/02/23 19:35:28 by yugao            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILE = $(addprefix ./srcs/, so_long_main.c draw.c matrix.c read_map.c error.c matrix2.c)
OFILE = $(CFILE:.c=.o)
CFLAG = -Wall -Wextra -Werror
LDFLAGS = -framework OpenGL -framework AppKit
LIBS = -L minilibx -lmlx
NAME = so_long

all:libft $(NAME)

$(NAME):$(OFILE)
	gcc $(OFILE) $(LIBS)  -fsanitize=address -L libft -lft $(LDFLAGS)  -o $@

%.o:%.c
	gcc $(CFLAG) -c -Imlx $< -o $@

libft:
	$(MAKE) -C libft

clean:
	rm -f $(OFILE)
	$(MAKE) fclean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) clean -C libft

re:fclean all

.PHONY: fclean clean libft