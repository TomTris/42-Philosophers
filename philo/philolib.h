/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:41:57 by qdo               #+#    #+#             */
/*   Updated: 2024/04/26 23:01:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork_mutex
{
	int				nbr;
	int				used;
	pthread_mutex_t	mutex;
}	t_fork_mutex;

typedef struct s_philo
{
	t_fork_mutex		*psfork;
	int					die;
	int					nbr;
	int					sum;
	int					group;
	int					group_sum;
	int					ate_times;
	struct timeval		start;
	struct timeval		end;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_die;
	pthread_t			*philo_id;
}	t_philo;


t_fork_mutex	*ft_fork_fill(t_philo *philo);
t_philo			*ft_philo_fill(int ac, char **av);
int				ft_time_count(t_philo *philo_i);
struct timeval	*ft_print_out(t_philo *philo_i, char *str);


#endif
