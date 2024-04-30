NAME = philo
CFLAGS = -Wall -Werror -Wextra
SRC = 	ft_fork_n_mutex_fill.c ft_philo_fill.c philo.c\
		ft_set_n_check_using_mutex.c ft_supervisor.c\
		ft_create.c ft_philojob.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all