CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -pthread

SRCS = main.c \
       utils.c \
	   init.c \
	   routine.c \
	   bigbrother.c 
	
OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	clear

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	clear
test : all clean
	./$(NAME) 5 800 400 300

leak: re
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./philo 4 310 200 100

drd: re
	valgrind --tool=drd ./philo 4 310 200 100

helgrind: re
	valgrind --tool=helgrind --history-level=approx ./philo 4 310 200 100

.PHONY: all clean fclean re debug
