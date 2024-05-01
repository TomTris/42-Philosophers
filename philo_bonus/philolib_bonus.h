/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 23:31:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/02 00:39:16 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_BONUS_H
# define PHILOLIB_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

//sem_print - only 1
//sem_ate_times - asmanyas philos- there will be a thread of main processes
//also try to sem_wait && sem_post all the time. If gettimeofday doesn't work
//any more -> it stop -> enough -> kill
//sem_fork - forks-number
typedef struct s_sm_philo
{
	int			du_die;
	short		du_eat;
	short		du_sleep;
	short		sum;
	short		nbr;
	short		must_eat;
	short		ate_times;
	pthread_t	super_thread;
	pid_t		*philos;
	size_t		time_to_die;
	sem_t		*sem_fork;
	sem_t		*sem_ate_times;
	sem_t		*sem_print;
	sem_t		*sem_super_prio;
	sem_t		*sem_fork_pair;
}	t_sm_philo;

//ft_philo_fill.c
int			ft_sm_philo_fill(int ac, char **av, t_sm_philo *philo);

//philo_bonus.c
void		ft_clean_programm(t_sm_philo *philo, char check);

//ft_time_funcs.c
size_t		ft_begin(int check);
size_t		ft_current_time(void);

//ft_create_bonus.c
void		ft_create_bonus(t_sm_philo *philo);

//ft_ms_phlojob.c

void		ft_sm_philojob(void *philo_data);

#endif