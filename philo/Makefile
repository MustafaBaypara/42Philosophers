NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread # -fsanitize=thread -g

CFILES = srcs/main.c srcs/events.c srcs/initialize.c \
		 srcs/utils.c srcs/utils2.c srcs/threads.c
OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re