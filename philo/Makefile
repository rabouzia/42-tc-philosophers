SRC	  =		src/main.c						\

NAME =		philo

CFLAGS =	-Wall -Wextra -g3 -I./inc

CC =		cc

OBJ_DIR		=	obj

OBJ = $(SRC:.c=.o)

all:		$(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir obj

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus