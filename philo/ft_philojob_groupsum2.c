/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philojob_groupsum2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:10:18 by qdo               #+#    #+#             */
/*   Updated: 2024/04/28 17:52:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_group2_eat(t_philo *philo_i, int fork_next);
static void	ft_group2(t_philo *philo_i, int fork_next);
static void	ft_group1_eat(t_philo *philo_i);
static void	ft_group1(t_philo *philo_i);

//while eating && sleeping
static void	ft_group2_eat(t_philo *philo_i, int fork_next)
{
	long int	cnt_time_of_acti;

	philo_i[0].psfork[philo_i[0].nbr].used = 2;
	philo_i[0].psfork[fork_next].used = 2;
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_next].mutex);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_set_time_to_die(philo_i);
	ft_print_out(philo_i, "finish eating");
	philo_i[0].start = philo_i[0].time_to_die;
	philo_i[0].ate_times++;
	while (1)
	{
		cnt_time_of_acti = ft_cnt_time_of_acti(philo_i);
		if (philo_i[0].time_sleep - 20 > cnt_time_of_acti)
			usleep((philo_i[0].time_sleep - cnt_time_of_acti) / 2);
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		if (ft_cnt_time_of_acti(philo_i) > philo_i[0].time_sleep)
			ft_group2(philo_i, fork_next);
	}
}

//wait for forks, take forks, start eating.
static void	ft_group2(t_philo *philo_i, int fork_next)
{
	long int	cnt_time_of_acti;

	while (1)
	{
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		if (philo_i[0].psfork[philo_i[0].nbr].used == 1
			&& philo_i[0].psfork[fork_next].used == 1)
			break ;
	}
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[fork_next].mutex);
	ft_print_out(philo_i, "eating");
	gettimeofday(&philo_i[0].start, NULL);
	while (1)
	{
		cnt_time_of_acti = ft_cnt_time_of_acti(philo_i);
		if (philo_i[0].time_eat - 20 > cnt_time_of_acti)
			usleep((philo_i[0].time_eat - cnt_time_of_acti) / 2);
		if (ft_check_die_philo(philo_i) == 1
			|| ft_cnt_time_of_acti(philo_i) > philo_i[0].time_eat)
			break ;
	}
	ft_group2_eat(philo_i, fork_next);
}

//while eating && sleeping
static void	ft_group1_eat(t_philo *philo_i)
{
	long int	cnt_time_of_acti;

	philo_i[0].psfork[philo_i[0].nbr].used = 1;
	philo_i[0].psfork[philo_i[0].nbr + 1].used = 1;
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_set_time_to_die(philo_i);
	ft_print_out(philo_i, "finish eating");
	philo_i[0].start = philo_i[0].time_to_die;
	philo_i[0].ate_times++;
	while (1)
	{
		cnt_time_of_acti = ft_cnt_time_of_acti(philo_i);
		if (philo_i[0].time_sleep - 20 > cnt_time_of_acti)
			usleep((philo_i[0].time_sleep - cnt_time_of_acti) / 2);
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		if (ft_cnt_time_of_acti(philo_i) > philo_i[0].time_sleep)
			ft_group1(philo_i);
	}
}

//wait for forks, take forks, start eating.
static void	ft_group1(t_philo *philo_i)
{
	long int	cnt_time_of_acti;

	while (1)
	{
		if (ft_check_die_philo(philo_i) == 1)
			return ;
		if (philo_i[0].psfork[philo_i[0].nbr].used == 2
			&& philo_i[0].psfork[philo_i[0].nbr + 1].used == 2)
			break ;
	}
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	ft_print_out(philo_i, "eating");
	gettimeofday(&philo_i[0].start, NULL);
	while (1)
	{
		cnt_time_of_acti = ft_cnt_time_of_acti(philo_i);
		if (philo_i[0].time_eat - 20 > cnt_time_of_acti)
			usleep((philo_i[0].time_eat - cnt_time_of_acti) / 2);
		if (ft_check_die_philo(philo_i) == 1
			|| ft_cnt_time_of_acti(philo_i) > philo_i[0].time_eat)
			break ;
	}
	ft_group1_eat(philo_i);
}

void	ft_philojob_groupsum2(t_philo *philo_i)
{
	int	fork_next;

	if (philo_i[0].group == 1)
		ft_group1(philo_i);
	else
	{
		if (philo_i[0].nbr != philo_i[0].sum)
			fork_next = philo_i[0].nbr + 1;
		else
			fork_next = 1;
		ft_group2(philo_i, fork_next);
	}
}

