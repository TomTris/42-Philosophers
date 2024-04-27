/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philojob_groupsum2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:10:18 by qdo               #+#    #+#             */
/*   Updated: 2024/04/27 13:00:39 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_philojob_groupsum2_group2_eat(t_philo *philo_i);
static void	ft_philojob_groupsum2_group2(t_philo *philo_i);
static void	ft_philojob_groupsum2_group1_eat(t_philo *philo_i);
static void	ft_philojob_groupsum2_group1(t_philo *philo_i);

//while eating && sleeping
static void	ft_philojob_groupsum2_group1_eat(t_philo *philo_i)
{
	while (1)
	{
		usleep((philo_i[0].time_eat - ft_cnt_time_of_acti(philo_i)) / 2);
		if (philo_i[0].die == 1)
			return ;
		if (ft_cnt_time_of_acti(philo_i) >= philo_i[0].time_eat)
		{
			gettimeofday(&philo_i[0].start, NULL);
			gettimeofday(&philo_i[0].time_to_die, NULL);
			pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
			pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
			ft_print_out(philo_i, "finish eating");
			philo_i[0].ate_times++;
			break ;
		}
	}
	while (1)
	{
		usleep((philo_i[0].time_sleep - ft_cnt_time_of_acti(philo_i)) * 0.7);
		if (philo_i[0].die == 1)
			return ;
		if (ft_cnt_time_of_acti(philo_i) >= philo_i[0].time_sleep)
			break ;
	}
	ft_philojob_groupsum2_group1(philo_i);
}

//wait for forks, take forks, start eating.
static void	ft_philojob_groupsum2_group1(t_philo *philo_i)
{
	while (1)
	{
		if (philo_i[0].psfork[philo_i[0].nbr].used == 2
			&& philo_i[0].psfork[philo_i[0].nbr + 1].used == 2)
			break ;
		if (philo_i[0].die == 1)
			return ;
	}
	gettimeofday(&philo_i[0].start, NULL);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	ft_print_out(philo_i, "eating");
	ft_philojob_groupsum2_group1_eat(philo_i);
}

static void	ft_philojob_groupsum2_group2_eat(t_philo *philo_i)
{
	while (1)
	{
		usleep((philo_i[0].time_eat - ft_cnt_time_of_acti(philo_i)) / 2);
		if (philo_i[0].die == 1)
			return ;
		if (ft_cnt_time_of_acti(philo_i) >= philo_i[0].time_eat)
		{
			gettimeofday(&philo_i[0].start, NULL);
			gettimeofday(&philo_i[0].time_to_die, NULL);
			ft_print_out(philo_i, "finish eating");
			pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
			pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr - 1].mutex);
			philo_i[0].ate_times++;
			break ;
		}
	}
	while (1)
	{
		usleep((philo_i[0].time_sleep - ft_cnt_time_of_acti(philo_i)) * 0.7);
		if (philo_i[0].die == 1)
			return ;
		if (ft_cnt_time_of_acti(philo_i) >= philo_i[0].time_sleep)
			break ;
	}
	ft_philojob_groupsum2_group2(philo_i);
}

static void	ft_philojob_groupsum2_group2(t_philo *philo_i)
{
	while (1)
	{
		if (philo_i[0].psfork[philo_i[0].nbr].used == 1
			|| philo_i[0].psfork[philo_i[0].nbr - 1].used == 1)
			break ;
		if (philo_i[0].die == 1)
			return ;
	}
	gettimeofday(&philo_i[0].start, NULL);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr - 1].mutex);
	ft_print_out(philo_i, "eating");
	ft_philojob_groupsum2_group2_eat(philo_i);
}

void	ft_philojob_groupsum2(t_philo *philo_i)
{
	if (philo_i[0].group == 1)
		ft_philojob_groupsum2_group1(philo_i);
	else
		ft_philojob_groupsum2_group2(philo_i);
}

