/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:38:35 by qdo               #+#    #+#             */
/*   Updated: 2024/04/26 22:52:44 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_t		*philo_id;
	int				i;

	philo_id = (pthread_t *)malloc((philo[0].nbr) + 1 * sizeof(pthread_t));
	if (philo_id == 0)
		return (1);
	philo = ft_philo_fill(ac, av);
	if (philo == 0)
		return (free(philo_id), 1);
	philo[0].psfork = ft_fork_fill(philo);
	if (philo[0].psfork == 0)
		return (free(philo_id), pthread_mutex_destroy(philo->mutex_print),
			free(philo->mutex_print), free(philo), 1);
	ft_philo_create(philo, philo_id);
	i = 0;
	while (++i <= philo[0].nbr)
		pthread_join(philo_id[i], NULL);
	return (free(philo_id), pthread_mutex_destroy(philo->mutex_print),
		free(philo->mutex_print), free(philo), 1);
}
