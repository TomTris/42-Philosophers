/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sm_philo_job.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:04:30 by qdo               #+#    #+#             */
/*   Updated: 2024/07/05 15:00:45 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

static char	ft_check_die(t_sm_philo *philo_i)
{
	if ((ft_current_time() - philo_i->time_to_die)
		>= (size_t) philo_i->du_die * 1000)
		return (1);
	return (0);
}

static void	ft_usleep(t_sm_philo *philo_i, size_t dura)
{
	size_t	start_cnt;

	start_cnt = ft_current_time();
	while (1)
	{
		if (ft_check_die(philo_i) == 1)
		{
			sem_wait(philo_i->sem_print);
			printf("%ld %d died\n",
				(ft_current_time() - ft_begin(0)) / 1000, philo_i->nbr);
			exit(EXIT_FAILURE);
		}
		if (ft_current_time() - start_cnt < dura * 1000)
			usleep(250);
		else
			return ;
	}
}

char	ft_strcmp(char *str1, char *str2)
{
	short	i;

	if (str1 == 0 || str2 == 0)
		return (0);
	i = 0;
	while (str1[i])
	{
		if (str1[i] == str2[i])
			i++;
		else
			break ;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}

static void	ft_print_out(t_sm_philo *philo_i, char *str)
{
	sem_wait(philo_i->sem_print);
	if (ft_check_die(philo_i) == 1)
	{
		printf("%ld %d died\n", (ft_current_time() - ft_begin(0)) / 1000,
			philo_i->nbr);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(str, "is eating") == 1)
		philo_i->time_to_die = ft_current_time();
	if (printf("%ld %d %s\n",
			(ft_current_time() - ft_begin(0)) / 1000, philo_i->nbr, str) == -1)
	{
		write(2, "printf error\n", 13);
		exit(EXIT_FAILURE);
	}
	sem_post(philo_i->sem_print);
}

void	ft_sm_philojob(void *philo_data)
{
	t_sm_philo			*philo_i;

	philo_i = (t_sm_philo *)philo_data;
	while (1)
	{
		ft_print_out(philo_i, "is thinking");
		sem_wait(philo_i->sem_fork_pair);
		sem_wait(philo_i->sem_fork);
		ft_print_out(philo_i, "has taken a fork");
		sem_wait(philo_i->sem_fork);
		ft_print_out(philo_i, "has taken a fork");
		ft_print_out(philo_i, "is eating");
		ft_usleep(philo_i, philo_i->du_eat);
		if (++(philo_i->ate_times) == philo_i->must_eat)
			sem_post(philo_i->sem_ate_times);
		sem_post(philo_i->sem_fork_pair);
		sem_post(philo_i->sem_fork);
		sem_post(philo_i->sem_fork);
		ft_print_out(philo_i, "is sleeping");
		ft_usleep(philo_i, philo_i->du_eat);
	}
}
