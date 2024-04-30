/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philojob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:15:58 by qdo               #+#    #+#             */
/*   Updated: 2024/04/30 23:13:34 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

//dura - dif_us
static void	ft_usleep(t_philo *philo_i, size_t dura)
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
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		gettimeofday(&now_tv, NULL);
		dif_us = (now_tv.tv_sec * 100000) + (now_tv.tv_usec / 10) - (start_us);
		if (dif_us < dura)
			usleep(250);
		else
			return ;
	}
}

static void	ft_take_fork(t_philo *philo_i, int fork_left, int fork_right)
{
	pthread_mutex_lock(&philo_i[0].psfork[fork_right].mutex);
	while (philo_i[0].psfork[fork_right].used == philo_i[0].group)
	{
		pthread_mutex_unlock(&philo_i[0].psfork[fork_right].mutex);
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		ft_usleep(philo_i, 1);
		pthread_mutex_lock(&philo_i[0].psfork[fork_right].mutex);
	}
	pthread_mutex_lock(&philo_i[0].psfork[fork_left].mutex);
	if (philo_i[0].psfork[fork_left].used == philo_i[0].group)
	{
		pthread_mutex_unlock(&philo_i[0].psfork[fork_right].mutex);
		pthread_mutex_unlock(&philo_i[0].psfork[fork_left].mutex);
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		ft_take_fork(philo_i, fork_left, fork_right);
	}
}

static void	ft_group_even(t_philo *philo_i, int fork_left, int fork_right)
{
	ft_print_out(philo_i, "is thinking");
	ft_take_fork(philo_i, fork_left, fork_right);
	ft_print_out(philo_i, "has taken a fork");
	ft_print_out(philo_i, "has taken a fork");
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i, philo_i[0].time_eat);
	philo_i[0].psfork[fork_left].used = philo_i[0].group;
	pthread_mutex_unlock(&philo_i[0].psfork[fork_left].mutex);
	ft_set_time_to_die(philo_i);
	philo_i[0].psfork[fork_right].used = philo_i[0].group;
	pthread_mutex_unlock(&philo_i[0].psfork[fork_right].mutex);
	if (++(philo_i[0].ate_times) == philo_i[0].must_eat)
		ft_set_ate_times(philo_i);
	ft_print_out(philo_i, "is sleeping");
	ft_usleep(philo_i, philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group_even(philo_i, fork_left, fork_right);
}

static void	ft_group_odd(t_philo *philo_i, short fork_left, short fork_right)
{
	ft_take_fork(philo_i, fork_left, fork_right);
	ft_print_out(philo_i, "has taken a fork");
	ft_print_out(philo_i, "has taken a fork");
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i, philo_i[0].time_eat);
	philo_i[0].psfork[fork_left].used = philo_i[0].group;
	pthread_mutex_unlock(&philo_i[0].psfork[fork_left].mutex);
	ft_set_time_to_die(philo_i);
	philo_i[0].psfork[fork_right].used = philo_i[0].group;
	pthread_mutex_unlock(&philo_i[0].psfork[fork_right].mutex);
	if (++(philo_i[0].ate_times) == philo_i[0].must_eat)
		ft_set_ate_times(philo_i);
	ft_print_out(philo_i, "is sleeping");
	ft_usleep(philo_i, philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_print_out(philo_i, "is thinking");
	ft_group_odd(philo_i, fork_left, fork_right);
}

void	ft_philojob(void *philo_data)
{
	short			fork_right;
	t_philo			*philo_i;

	philo_i = (t_philo *)philo_data;
	if (philo_i[0].group == 1)
	{
		fork_right = philo_i[0].nbr + 1;
		ft_group_odd(philo_i, philo_i[0].nbr, fork_right);
		return ;
	}
	if (philo_i[0].nbr != philo_i[0].sum)
		fork_right = philo_i[0].nbr + 1;
	else
		fork_right = 1;
	if (philo_i[0].group == 2)
		ft_group_even(philo_i, philo_i[0].nbr, fork_right);
	else
	{
		ft_print_out(philo_i, "is thinking");
		ft_group_odd(philo_i, philo_i[0].nbr, fork_right);
	}
}
