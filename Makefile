CC = gcc

NAME = philo

HEADER_NAME = philo.h

CFLAGS = -Wall -Wextra -Werror

SRCS =  philo.c  \
		utils.c check_arg.c \
		init.c \
		routine.c \
		time_utils.c \
		monitor.c \
		actions.c \
		handle_mutex.c \
		handle_thread.c \
		ft_free.c \

OBJS = ${SRCS:.c=.o}

all:	${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c Makefile $(HEADER_NAME)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
