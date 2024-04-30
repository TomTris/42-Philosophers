/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_n_mutex_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:07:21 by qdo               #+#    #+#             */
/*   Updated: 2024/04/30 23:26:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static int	ft_malloc_mutex(t_philo *philo)
{
	philo[0].mutex_print = (pthread_mutex_t *)malloc
		(1 * sizeof(pthread_mutex_t));
	if (philo[0].mutex_print == 0)
		return (0);
	philo[0].mutex_ate_times = (t_list_mutex *)malloc
		(1 * sizeof(t_list_mutex));
	if (philo[0].mutex_ate_times == 0)
		return (0);
	philo[0].psfork = (t_list_mutex *)malloc
		((philo[0].sum + 1) * sizeof(t_list_mutex));
	if (philo[0].psfork == 0)
		return (0);
	philo[0].mutex_die = (t_list_mutex *)malloc
		((philo[0].sum + 1) * sizeof(t_list_mutex));
	if (philo[0].mutex_die == 0)
		return (0);
	philo[0].mutex_time_to_die = (t_list_mutex *)malloc
		((philo[0].sum + 1) * sizeof(t_list_mutex));
	if (philo[0].mutex_time_to_die == 0)
		return (0);
	return (1);
}

static int	ft_del(t_philo *philo)
{
	free(philo[0].mutex_print);
	free(philo[0].psfork);
	free(philo[0].mutex_ate_times);
	free(philo[0].mutex_die);
	free(philo[0].mutex_time_to_die);
	philo[0].mutex_print = 0;
	philo[0].psfork = 0;
	philo[0].mutex_ate_times = 0;
	philo[0].mutex_die = 0;
	philo[0].mutex_time_to_die = 0;
	return (0);
}

//philo[0].mutex_ate_times[0].nbr will be definately < 0 when there is error.
//=> is used for checking error, for printf == -1;
static int	ft_mutex_handle(t_philo *philo, int i)
{
	while (++i <= philo[0].sum)
	{
		philo[0].psfork[i].nbr = -1;
		philo[0].mutex_die[i].nbr = -1;
		philo[0].mutex_time_to_die[i].nbr = -1;
	}
	i = 0;
	while (++i <= philo[0].sum)
	{
		philo[i].mutex_print = philo[0].mutex_print;
		philo[i].mutex_ate_times = philo[0].mutex_ate_times;
		if (pthread_mutex_init(&philo[0].psfork[i].mutex, NULL) != 0)
			return (0);
		philo[0].psfork[i].nbr = i;
		philo[i].psfork = philo[0].psfork;
		if (pthread_mutex_init(&philo[0].mutex_die[i].mutex, NULL) != 0)
			return (0);
		philo[0].mutex_die[i].nbr = i;
		philo[i].mutex_die = &philo[0].mutex_die[i];
		if (pthread_mutex_init(&philo[0].mutex_time_to_die[i].mutex, NULL) != 0)
			return (0);
		philo[0].mutex_time_to_die[i].nbr = i;
		philo[i].mutex_time_to_die = &philo[0].mutex_time_to_die[i];
	}
	return (1);
}

static int	ft_destroy_becauseof_fail(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].sum)
	{
		if (philo[0].psfork[i].nbr != -1)
			pthread_mutex_destroy(&(philo[0].psfork[i].mutex));
		if (philo[0].mutex_die[i].nbr != -1)
			pthread_mutex_destroy(&(philo[0].mutex_die[i].mutex));
		if (philo[0].mutex_time_to_die[i].nbr != -1)
			pthread_mutex_destroy(&(philo[0].mutex_time_to_die[i].mutex));
	}
	pthread_mutex_destroy(philo[0].mutex_print);
	pthread_mutex_destroy(&(philo[0].mutex_ate_times[0].mutex));
	return (ft_del(philo));
}

int	ft_fork_n_mutex_fill(t_philo *philo)
{
	int	i;

	philo[0].mutex_print = 0;
	philo[0].mutex_ate_times = 0;
	philo[0].psfork = 0;
	philo[0].mutex_die = 0;
	philo[0].mutex_time_to_die = 0;
	if (ft_malloc_mutex(philo) == 0)
		return (ft_del(philo));
	if (pthread_mutex_init(philo[0].mutex_print, NULL) != 0)
		return (ft_del(philo));
	if (pthread_mutex_init(&(philo[0].mutex_ate_times[0].mutex), NULL) != 0)
		return (pthread_mutex_destroy(philo[0].mutex_print), ft_del(philo));
	philo[0].mutex_ate_times[0].nbr = 0;
	if (ft_mutex_handle(philo, 0) == 0)
		return (ft_destroy_becauseof_fail(philo));
	philo[0].psfork[1].used = philo[0].group_sum;
	i = 1;
	while (++i < philo[0].sum)
		philo[0].psfork[i].used = 2;
	philo[0].psfork[i].used = philo[0].group_sum;
	return (1);
}
