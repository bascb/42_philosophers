NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRC = philosophers utils process_input check_input clean_memory gathering_management
LIBS = -pthread

RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
	
all: $(NAME)

$(NAME): $(SRC:=.o)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC:=.o) $(LIBS)
	
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus