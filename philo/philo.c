/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:38:35 by qdo               #+#    #+#             */
/*   Updated: 2024/04/27 13:22:17 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_destroy_n_free_pthread_mutex_psfork(t_philo *philo)
{
	int	i;

	if (philo[0].psfork != NULL)
	{
		i = 0;
		while (++i <= philo[0].sum)
			pthread_mutex_destroy(&philo[0].psfork[i].mutex);
		free(philo[0].psfork);
	}
	pthread_mutex_destroy(philo[0].mutex_print);
	free(philo[0].mutex_print);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_t		*philo_id;

	philo = ft_philo_fill(ac, av);
	if (philo == 0)
		return (1);
	philo_id = (pthread_t *)malloc((philo[0].nbr) + 1 * sizeof(pthread_t));
	if (philo_id == 0)
		return (ft_destroy_n_free_pthread_mutex_psfork(philo), 1);
	philo[0].psfork = ft_fork_fill(philo);
	if (philo[0].psfork == 0)
		return (ft_destroy_n_free_pthread_mutex_psfork(philo),
			free(philo_id), 1);
	ft_philo_create(philo, philo_id);
	return (ft_destroy_n_free_pthread_mutex_psfork(philo),
		free(philo_id), 0);
}
