NAME     =		philo

SRC	     =		src/check_utils.c	\
				src/clean_tools.c 	\
				src/init.c  	\
				src/lst_utils.c 	\
				src/main.c 			\
			    src/mini_libft.c	\
				src/routine.c 		\
				src/time_tools.c 	\


CC       =	    cc

CFLAGS   =	    -Wall -Wextra -Werror -g3 -I./inc

OBJ_DIR	 =	    obj/

SRCS     =      $(SRC)

OBJ 	 =      $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =      mkdir -p

SMAKE	 =      make --no-print-directory

all:	        $(NAME)

$(NAME):        $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $@ -pthread
				
$(OBJ_DIR)%.o:  src/%.c
			    @mkdir -p $(OBJ_DIR)
			    @$(CC) $(CFLAGS) -c $< -o $@ 

clean:
				@rm -rf $(OBJ_DIR)
				@echo "\033[1;31m======== philo object files removed ========\033[0m"

fclean:         clean
				@$(RM) $(NAME)
				@echo "\033[1;31m======= philo executable removed =======\033[0m"

re:             fclean
				@$(SMAKE)

.PHONY: clean fclean all re
