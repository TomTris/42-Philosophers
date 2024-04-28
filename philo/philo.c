/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:38:35 by qdo               #+#    #+#             */
/*   Updated: 2024/04/28 16:52:27 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_destroy_n_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].sum)
	{
		if (philo[0].psfork != 0)
			pthread_mutex_destroy(&philo[0].psfork[i].mutex);
		if (philo[0].mutex_ate_times != 0)
			pthread_mutex_destroy(&philo[0].mutex_ate_times[i].mutex);
		if (philo[0].mutex_die != 0)
			pthread_mutex_destroy(&philo[0].mutex_die[i].mutex);
		if (philo[0].mutex_start != 0)
			pthread_mutex_destroy(&philo[0].mutex_start[i].mutex);
		if (philo[0].mutex_time_to_die != 0)
			pthread_mutex_destroy(&philo[0].mutex_time_to_die[i].mutex);
	}
	pthread_mutex_destroy(philo[0].mutex_print);
	free(philo[0].mutex_ate_times);
	free(philo[0].mutex_die);
	free(philo[0].mutex_print);
	free(philo[0].mutex_start);
	free(philo[0].mutex_time_to_die);
	free(philo[0].philo_id);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;

	philo = ft_philo_fill(ac, av);
	if (philo == 0)
		return (1);
	if (ft_fork_n_mutex_fill(philo) == 0)
		return (ft_destroy_n_free(philo), 1);
	ft_philo_create(philo, philo[0].philo_id);
	return (ft_destroy_n_free(philo), 1);
}
