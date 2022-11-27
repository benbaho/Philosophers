NAME = philo
SRC = $(shell find . -name "*.c")
FLAGS = -Wall -Wextra -Werror
CC = gcc -g 
OBJ = $(SRC:.c=.o)
RM = rm -rf

all: $(NAME)


$(NAME): $(OBJ) 
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	
re:	fclean all

norm:
	norminette *.c
	norminette *.h

.PHONY: all re fclean clean norm