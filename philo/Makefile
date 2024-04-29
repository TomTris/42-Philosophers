NAME = philo
CFLAGS = -Wall -Werror -Wextra
SRC = ft_create.c ft_fork_n_mutex_fill.c ft_philo_fill.c  philo.c\
		ft_philojob.c\
		ft_set_n_check_using_mutex_1.c ft_set_n_check_using_mutex_2.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all