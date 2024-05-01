/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 23:31:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 02:47:32 by qdo              ###   ########.fr       */
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

//sem_print - only 1
//sem_ate_times - asmanyas philos- there will be a thread of main processes
//also try to sem_wait && sem_post all the time. If gettimeofday doesn't work
//any more -> it stop -> enough -> kill
//sem_fork - forks-number
typedef struct s_sm_philo
{
	short		du_die;
	short		du_eat;
	short		du_sleep;
	short		sum;
	short		nbr;
	char		group;
	char		group_sum;
	char		die;
	short		must_eat;
	short		ate_times;
	pid_t		*philos;
	size_t		time_to_die;
	sem_t		*sem_fork;
	sem_t		*sem_ate_times;
	sem_t		*sem_print;
}	t_sm_philo;

t_sm_philo	*ft_sm_philo_fill(int ac, char **av, t_sm_philo *philo);
void		ft_clean_programm(t_sm_philo *philo, char check);

#endif