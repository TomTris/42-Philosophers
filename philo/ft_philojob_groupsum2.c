/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philojob_groupsum2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:10:18 by qdo               #+#    #+#             */
/*   Updated: 2024/04/29 00:19:56 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_usleep(int time_in_milisecond)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if (((((double)now.tv_usec - start.tv_usec))
				+ (((double)now.tv_sec - start.tv_sec) * 1000000))
			< ((double)time_in_milisecond * 1000))
			usleep(((time_in_milisecond * 1000)
					- (((now.tv_usec - start.tv_usec))
						+ ((now.tv_sec - start.tv_sec) * 1000000))) / 10);
		else
			return ;
	}
}

static void	ft_group2(t_philo *philo_i, int fork_next)
{
	ft_print_out(philo_i, "is thinking");
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[fork_next].mutex);
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_next].mutex);
	ft_print_out(philo_i, "is sleeping");
	philo_i[0].ate_times++;
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group2(philo_i, fork_next);
}

static void	ft_group1(t_philo *philo_i)
{
	ft_print_out(philo_i, "is thinking");
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	ft_print_out(philo_i, "is sleeping");
	philo_i[0].ate_times++;
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group1(philo_i);
}

void	ft_philojob_groupsum2(t_philo *philo_i)
{
	int	fork_next;

	if (philo_i[0].group == 1)
		ft_group1(philo_i);
	else
	{
		ft_print_out(philo_i, "is thinking");
		if (philo_i[0].nbr != philo_i[0].sum)
			fork_next = philo_i[0].nbr + 1;
		else
			fork_next = 1;
		usleep(philo_i[0].time_eat * 500);
		ft_group2(philo_i, fork_next);
	}
}

