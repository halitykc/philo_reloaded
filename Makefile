CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -pthread

SRCS = main.c \
       utils.c \
	   init.c \
	   routine.c
OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test : all clean
	./$(NAME) 5 800 400 300

.PHONY: all clean fclean re debug
