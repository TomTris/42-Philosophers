NAME = philo_bonus
CFLAGS = -Wall -Werror -Wextra
SRC = ft_create_bonus.c ft_sm_philo_job.c\
		ft_philo_fill.c ft_time_funcs.c\
		philo_bonus.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)
re: fclean all