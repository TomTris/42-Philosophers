/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philojob_no_must_eat.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:31:07 by qdo               #+#    #+#             */
/*   Updated: 2024/04/29 17:55:51 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_usleep(size_t dura)
{
	struct timeval	start_tv;
	struct timeval	now_tv;
	size_t			start_us;
	size_t			dif_us;

	gettimeofday(&start_tv, NULL);
	dura *= 100;
	start_us = (start_tv.tv_sec * 100000) + (start_tv.tv_usec / 10);
	while (1)
	{
		gettimeofday(&now_tv, NULL);
		dif_us = (now_tv.tv_sec * 100000) + (now_tv.tv_usec / 10) - (start_us);
		if (dif_us < dura)
			usleep((dura - dif_us));
		else
			return ;
	}
}

static void	ft_group23(t_philo *philo_i, int fork_left, int fork_right)
{
	ft_print_out(philo_i, "is thinking");
	pthread_mutex_lock(&philo_i[0].psfork[fork_right].mutex);
	ft_print_out(philo_i, "has taken a fork");
	pthread_mutex_lock(&philo_i[0].psfork[fork_left].mutex);
	ft_print_out(philo_i, "has taken a fork");
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_right].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_left].mutex);
	ft_print_out(philo_i, "is sleeping");
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group23(philo_i, fork_left, fork_right);
}

static void	ft_group(t_philo *philo_i, int fork_left, int fork_right)
{
	pthread_mutex_lock(&philo_i[0].psfork[fork_right].mutex);
	ft_print_out(philo_i, "has taken a fork");
	pthread_mutex_lock(&philo_i[0].psfork[fork_left].mutex);
	ft_print_out(philo_i, "has taken a fork");
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_right].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_left].mutex);
	ft_print_out(philo_i, "is sleeping");
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_print_out(philo_i, "is thinking");
	ft_group(philo_i, fork_left, fork_right);
}

void	ft_philojob_no_must_eat(void *philo_data)
{
	int				fork_right;
	t_philo			*philo_i;

	philo_i = (t_philo *)philo_data;
	if (philo_i[0].group == 1)
	{
		fork_right = philo_i[0].nbr + 1;
		ft_group(philo_i, philo_i[0].nbr, fork_right);
		return ;
	}
	if (philo_i[0].nbr != philo_i[0].sum)
		fork_right = philo_i[0].nbr + 1;
	else
		fork_right = 1;
	if (philo_i[0].group == 2)
	{
		usleep(philo_i[0].time_eat * 500);
		ft_group23(philo_i, philo_i[0].nbr, fork_right);
	}
	else
	{
		usleep(philo_i[0].time_eat * 1500);
		ft_group23(philo_i, philo_i[0].nbr, fork_right);	
	}
}
