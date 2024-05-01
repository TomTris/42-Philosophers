/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:38:35 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 02:07:22 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_error_report(t_philo *philo_i)
{
	pthread_mutex_lock(&(philo_i[0].mutex_ate_times[0].mutex));
	philo_i[0].mutex_ate_times[0].nbr = -10 - philo_i[0].sum;
	write(2, "printf func error\n", 18);
	pthread_mutex_unlock(&(philo_i[0].mutex_ate_times[0].mutex));
}

static void	ft_destroy_n_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].sum)
	{
		if (philo[0].psfork != 0)
			pthread_mutex_destroy(&philo[0].psfork[i].mutex);
		if (philo[0].mutex_die != 0)
			pthread_mutex_destroy(&philo[0].mutex_die[i].mutex);
		if (philo[0].mutex_time_to_die != 0)
			pthread_mutex_destroy(&philo[0].mutex_time_to_die[i].mutex);
	}
	pthread_mutex_destroy(philo[0].mutex_print);
	pthread_mutex_destroy(&(philo[0].mutex_ate_times[0].mutex));
	free(philo[0].psfork);
	free(philo[0].mutex_ate_times);
	free(philo[0].mutex_die);
	free(philo[0].mutex_print);
	free(philo[0].mutex_time_to_die);
	free(philo[0].philo_id);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	int				check;

	philo = ft_philo_fill(ac, av);
	if (philo == 0)
		return (1);
	if (philo[0].must_eat == 0)
		return (free(philo), 0);
	if (ft_fork_n_mutex_fill(philo) == 0)
		return (ft_destroy_n_free(philo), 1);
	check = ft_philo_create(philo, philo[0].philo_id);
	if (check == 1 && philo[0].mutex_ate_times[0].nbr >= 0)
		check = 1;
	else
		check = -1;
	ft_destroy_n_free(philo);
	return (check);
}
