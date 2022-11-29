NAME = philo
SRC = $(shell find . -name "*.c")
FLAGS = -Wall -Wextra -Werror
CC = @gcc -g
OBJ = $(SRC:.c=.o)
RM = rm -rf

all: $(NAME)


$(NAME): $(OBJ) 
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)
		@echo "\x1B[35m"Compile Done!"\x1b[0m"

clean:
	@$(RM) $(OBJ)
	@echo "\x1b[36m"Object files deleted."\x1b[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\x1b[36m"Program deleted."\x1b[0m"
	
re:	fclean all

norm:
	norminette *.c
	norminette *.h

.PHONY: all re fclean clean norm