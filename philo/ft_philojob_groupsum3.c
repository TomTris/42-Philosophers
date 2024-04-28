/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philojob_groupsum3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:31:07 by qdo               #+#    #+#             */
/*   Updated: 2024/04/29 00:20:38 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_group3(t_philo *philo_i, int fork_next)
{
	ft_print_out(philo_i, "is thinking");
	pthread_mutex_lock(&philo_i[0].psfork[fork_next].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_next].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_print_out(philo_i, "is sleeping");
	philo_i[0].ate_times++;
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group3(philo_i, fork_next);
}

static void	ft_group2(t_philo *philo_i, int fork_next)
{
	ft_print_out(philo_i, "is thinking");
	pthread_mutex_lock(&philo_i[0].psfork[fork_next].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[fork_next].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_print_out(philo_i, "is sleeping");
	philo_i[0].ate_times++;
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group2(philo_i, fork_next);
}

//wait for forks, take forks, start eating.
static void	ft_group1(t_philo *philo_i)
{
	ft_print_out(philo_i, "is thinking");
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	pthread_mutex_lock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_print_out(philo_i, "is eating");
	ft_usleep(philo_i[0].time_eat);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr + 1].mutex);
	ft_set_time_to_die(philo_i);
	pthread_mutex_unlock(&philo_i[0].psfork[philo_i[0].nbr].mutex);
	ft_print_out(philo_i, "is sleeping");
	philo_i[0].ate_times++;
	ft_usleep(philo_i[0].time_sleep);
	if (ft_check_die_philo(philo_i) == 1)
		return ;
	ft_group1(philo_i);
}

void	ft_philojob_groupsum3(t_philo *philo_i)
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
		if (philo_i[0].group == 2)
		{
			usleep(philo_i[0].time_eat * 500);
			ft_group2(philo_i, fork_next);
		}
		else
		{
			usleep(philo_i[0].time_eat * 1500);
			ft_group3(philo_i, fork_next);	
		}
	}
}

