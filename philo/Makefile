
NAME =		philo

SRC	  =		src/main.c					

CC =		cc
CFLAGS =	-Wall -Wextra -g3 -I./inc

OBJ_DIR		=	obj

OBJ = $(SRC:.c=.o)

SMAKE		= make --no-print-directory

all:		$(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) -o $@ $^
		@echo "\033[1;32m           __    _ __                       __                  "
		@echo "    ____  / /_  (_) /___  _________  ____  / /_  ___  __________"
		@echo "   / __ \/ __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/"
		@echo "  / /_/ / / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) "
		@echo " / .___/_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  "
		@echo "/_/                              /_/                            \n\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir obj

clean:
		@clear
		@$(RM) -R $(PATH_OBJS)
		@echo "\033[1;31m======== philo object files removed ========\033[0m"

fclean: clean
		@clear
		@$(RM) $(NAME)
		@echo "\033[1;31m======= philo executable removed =======\033[0m"

re: fclean
	@$(SMAKE)

.PHONY: clean fclean all re bonus