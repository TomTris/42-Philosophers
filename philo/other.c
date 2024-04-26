/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:55 by qdo               #+#    #+#             */
/*   Updated: 2024/04/26 23:40:37 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	ft_time_count(t_philo *philo_i, int check)
{
	static struct timeval	*begin;

	if (philo_i == 0 && check == -1)
	{
		begin = ft_print_out(NULL, NULL);
		return (0);
	}
	if (check == 1 && philo_i->ate_times == 0)
	{
		gettimeofday(&philo_i->end, NULL);
		return ((philo_i->end.tv_usec - begin->tv_usec) / 1000);
	}
	else
	{
		gettimeofday(&philo_i->end, NULL);
		return ((philo_i->end.tv_usec - philo_i->start.tv_usec) / 1000);
	}
}

struct timeval	*ft_print_out(t_philo *philo_i, char *str)
{
	static struct timeval	*begin = NULL;
	struct timeval			now;

	if (begin == NULL)
	{
		begin = (struct timeval *)malloc(1 * sizeof(struct timeval));
		if (begin == 0)
			return (NULL);
		gettimeofday(begin, NULL);
		return (begin);
	}
	else if (philo_i != 0 && str != 0)
	{
		pthread_mutex_lock(philo_i->mutex_print);
		gettimeofday(&now, NULL);
		if (philo_i->die == 0)
			printf("%d %d %s\n", (now.tv_usec - begin->tv_usec) / 1000,
				philo_i->nbr, str);
		pthread_mutex_unlock(philo_i->mutex_print);
	}
	return (begin);
}
