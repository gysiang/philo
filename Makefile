# Compiler and Flags
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I./includes

# Directories
SRC_DIR			= src

SRC_FILES		= $(addprefix $(SRC_DIR)/, \
					main.c)

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
