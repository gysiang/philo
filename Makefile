# Compiler and Flags
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I./includes

# Directories
SRC_DIR			= src

SRC_FILES		= $(addprefix $(SRC_DIR)/, \
					check_input.c \
					init.c \
					main.c \
					observer.c \
					routine.c \
					threads.c \
					time.c \
					utils.c)

OBJECTS			= $(SRC_FILES:.c=.o)

NAME			= philo

#Targets

all:		$(NAME)

$(NAME):	$(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
		rm -f $(OBJECTS)

fclean: clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
