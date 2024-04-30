/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:41:57 by qdo               #+#    #+#             */
/*   Updated: 2024/04/30 02:06:11 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_list_mutex
{
	int				nbr;
	pthread_mutex_t	mutex;
}	t_list_mutex;

typedef struct s_philo
{
	t_list_mutex		*psfork;
	int					die;
	t_list_mutex		*mutex_die;
	int					nbr;
	int					sum;
	int					group;
	int					group_sum;
	int					ate_times;
	t_list_mutex		*mutex_ate_times;
	struct timeval		time_to_die;
	t_list_mutex		*mutex_time_to_die;
	struct timeval		start;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	pthread_mutex_t		*mutex_print;
	pthread_t			*philo_id;
}	t_philo;

void			ft_error_report(t_philo *philo);
int				ft_fork_n_mutex_fill(t_philo *philo);
t_philo			*ft_philo_fill(int ac, char **av);

void			ft_philojob_no_must_eat(void *philo_data);
int				ft_philo_create_no_must_eat(t_philo *philo,
					pthread_t *philo_id);

void			ft_philojob_with_must_eat(void *philo_data);
int				ft_philo_create_with_must_eat(t_philo *philo,
					pthread_t *philo_id);

void			ft_set_time_to_die(t_philo *philo_i);
int				ft_check_die_philo(t_philo *philo_i);
int				ft_check_ate_times(t_philo *philo_i);
void			ft_set_ate_times(t_philo *philo_i);
struct timeval	*ft_print_out(t_philo *philo_i, char *str);

#endif
