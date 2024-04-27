NAME = philo
CFLAGS = -Wall -Werror -Wextra
SRC = ft_create.c ft_fork_fill.c ft_philo_fill.c other.c philo.c\
		ft_philojob_groupsum2.c ft_philojob_groupsum3.c 
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re: fclean all