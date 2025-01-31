CC = gcc

CFLAGS = -c -Wall -Wextra -Werror
LFLAGS = -lpthread

NAME = philo

SRC = philo.c philo_utils.c philo_utils_2.c input.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean re
