/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:27:25 by qdo               #+#    #+#             */
/*   Updated: 2024/05/02 14:51:47 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

//kill to i - 1 childprocess, exit with "check" value
static void	ft_kill(t_sm_philo *philo, short i)
{
	short	j;

	j = 0;
	while (++j < i)
	{
		kill(philo->philos[j], SIGKILL);
		sem_post(philo->sem_ate_times);
		sem_post(philo->sem_fork);
		sem_post(philo->sem_fork_pair);
	}
}

//a thread die first -> detach, sem_post_sem_ate_times to release sem_wait,
//sem_super_prio to make sure, even these two happens at the same time, we also
//can release sem_super_prio
static void	ft_parent_job(t_sm_philo *philo)
{
	waitpid(-1, 0, 0);
	sem_wait(philo->sem_super_prio);
	if (philo->nbr == -1)
	{
		pthread_detach(philo->super_thread);
		ft_kill(philo, philo->sum);
		ft_clean_programm(philo, EXIT_SUCCESS);
	}
	ft_kill(philo, philo->sum + 1);
	philo->nbr = -1;
	sem_post(philo->sem_super_prio);
	usleep(500 * 1000);
	sem_wait(philo->sem_super_prio);
	pthread_detach(philo->super_thread);
	ft_clean_programm(philo, EXIT_FAILURE);
}

//philo->nbr == -1 -> ate_times reached, kill func: so that main thread wakes up
static void	ft_super_ate_times(void *philo_data)
{
	int			i;
	t_sm_philo	*philo;

	philo = (t_sm_philo *)philo_data;
	i = 0;
	while (++i <= philo->sum)
		sem_wait(philo->sem_ate_times);
	sem_wait(philo->sem_super_prio);
	if (philo->nbr != -1)
	{
		philo->nbr = -1;
		kill(philo->philos[philo->sum], SIGKILL);
	}
	sem_post(philo->sem_super_prio);
	while (1)
		usleep(10 * 1000 * 1000);
}

static void	ft_philos_pid_create(t_sm_philo *philo)
{
	philo->philos = (pid_t *)malloc((philo->sum + 1) * sizeof(pid_t));
	if (philo->philos == 0)
		ft_clean_programm(philo, EXIT_FAILURE);
}

void	ft_create_bonus(t_sm_philo *philo)
{
	int			i;

	ft_philos_pid_create(philo);
	ft_begin(1);
	pthread_create(&philo->super_thread, NULL,
		(void *)ft_super_ate_times, (void *)philo);
	i = 0;
	while (++i <= philo->sum)
	{
		philo->philos[i] = fork();
		if (philo->philos[i] < 0)
		{
			write(2, "fork error\n", 11);
			ft_kill(philo, i);
			ft_clean_programm(philo, EXIT_FAILURE);
		}
		else if (philo->philos[i] == 0)
		{
			philo->nbr = i;
			philo->time_to_die = ft_begin(0);
			ft_sm_philojob(philo);
			exit(EXIT_FAILURE);
		}
	}
	ft_parent_job(philo);
}
