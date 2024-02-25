SRCS = main.c error.c str.c thread.c utils.c
CFILE = $(addprefix ./srcs/, $(SRCS))
OFILE = $(CFILE:.c=.o)
HDIR = ./header
NAME = philo
CFLAG = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME):$(OFILE)
	$(CC) $(CFLAG) $^ -I $(HDIR) -o $@
%.o:%.c
	$(CC) $(CFLAG) -c $< -I $(HDIR) -o $@

clean:
	$(RM) -f $(OFILE)
fclean: clean
	$(RM) -f $(NAME)
re: fclean all

.PHONY: clean re