NAME = push_swap
CFILE = push_swap_dig_base.c push_swap_list_base1.c push_swap_list_base2.c push_swap_list_base3.c push_swap_list_base4.c push_swap_main.c push_swap_error_control.c push_swap_output.c
OFILE = $(CFILE:.c=.o)
FLAG = -Wall -Wextra -Werror


all:$(NAME)

$(NAME): $(OFILE)
	gcc $(FLAG) -o $(NAME) $^
%.o:%.c
	gcc $(FLAG) -o $@ -c $<

clean:
	rm -rf $(OFILE)

fclean: clean
	rm -rf $(NAME)

re: fclean all;

.PHONY: clean fclean re