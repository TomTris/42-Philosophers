/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_n_mutex_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:07:21 by qdo               #+#    #+#             */
/*   Updated: 2024/04/29 17:55:35 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_set_0(t_philo *philo)
{
	philo[0].mutex_print = 0;
	philo[0].mutex_ate_times = 0;
	philo[0].mutex_die = 0;
	philo[0].mutex_time_to_die = 0;
	philo[0].psfork = 0;
}

static int	ft_malloc_mutex(t_philo *philo)
{
	philo[0].mutex_print = (pthread_mutex_t *)malloc
		(2 * sizeof(pthread_mutex_t));
	if (philo[0].mutex_print == 0)
		return (0);
	philo[0].mutex_ate_times = (t_list_mutex *)malloc
		(2 * sizeof(t_list_mutex));
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
	if (philo[0].psfork == 0)
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

//handle philo[0].psfork[i].used = 2; later
static void	ft_mutex_handle(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(philo[0].mutex_print, NULL);
	pthread_mutex_init(&(philo[0].mutex_ate_times[0].mutex), NULL);
	while (++i <= philo[0].sum)
	{
		philo[i].mutex_print = philo[0].mutex_print;
		philo[i].mutex_ate_times = philo[0].mutex_ate_times;
		pthread_mutex_init(&philo[0].psfork[i].mutex, NULL);
		philo[0].psfork[i].nbr = i;
		philo[i].psfork = philo[0].psfork;
		pthread_mutex_init(&philo[0].mutex_die[i].mutex, NULL);
		philo[0].mutex_die[i].nbr = i;
		philo[i].mutex_die = &philo[0].mutex_die[i];
		pthread_mutex_init(&philo[0].mutex_time_to_die[i].mutex, NULL);
		philo[0].mutex_time_to_die[i].nbr = i;
		philo[i].mutex_time_to_die = &philo[0].mutex_time_to_die[i];
	}
}

int	ft_fork_n_mutex_fill(t_philo *philo)
{
	ft_set_0(philo);
	if (ft_malloc_mutex(philo) == 0)
		return (ft_del(philo));
	ft_mutex_handle(philo);
	return (1);
}
