/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:41:57 by qdo               #+#    #+#             */
/*   Updated: 2024/04/27 14:04:51 by qdo              ###   ########.fr       */
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
	struct timeval		time_to_die;
	struct timeval		start;
	struct timeval		end;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	pthread_mutex_t		*mutex_print;
}	t_philo;


t_fork_mutex	*ft_fork_fill(t_philo *philo);
t_philo			*ft_philo_fill(int ac, char **av);
long int		ft_cnt_time_of_acti(t_philo *philo_i);
struct timeval	*ft_print_out(t_philo *philo_i, char *str);
void			ft_philo_create(t_philo *philo, pthread_t *philo_id);
void			ft_philojob_groupsum2(t_philo *philo);
void			ft_philojob_groupsum3(t_philo *philo);

#endif
