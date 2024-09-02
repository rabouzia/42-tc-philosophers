NAME     =		philo

SRC	     =		src/main.c		\
			    src/libft.c		\
				src/init.c  	\
				src/lst_utils.c \
				src/time_handling.c 


CC       =	    cc

CFLAGS   =	    -Wall -Wextra -g3 -I./inc

OBJ_DIR	 =	    obj/

SRCS     =      $(SRC)

OBJ 	 =      $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =      mkdir -p

SMAKE	 =      make --no-print-directory

all:	        $(NAME)

$(NAME):        $(OBJ)
				# @clear
				@$(CC) $(CFLAGS) $(OBJ) -o $@ -pthread
				@echo "\033[1;32m           __    _ __                       __                  "
				@echo "    ____  / /_  (_) /___  _________  ____  / /_  ___  __________"
				@echo "   / __ \/ __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/"
				@echo "  / /_/ / / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) "
				@echo " / .___/_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  "
				@echo "/_/                              /_/                            \n\033[0m"

$(OBJ_DIR)%.o:  src/%.c
			    @mkdir -p $(OBJ_DIR)
			    @$(CC) $(CFLAGS) -c $< -o $@ 

clean:
				# @clear
				@rm -rf $(OBJ_DIR)
				@echo "\033[1;31m======== philo object files removed ========\033[0m"

fclean:         clean
				# @clear
				@$(RM) $(NAME)
				@echo "\033[1;31m======= philo executable removed =======\033[0m"

re:             fclean
				@$(SMAKE)

.PHONY: clean fclean all re
