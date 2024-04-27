/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:55 by qdo               #+#    #+#             */
/*   Updated: 2024/04/27 12:10:20 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

int	ft_cnt_time_to_die(t_philo *philo_i)
{
	gettimeofday(&philo_i[0].end, NULL);
	return ((philo_i[0].end.tv_usec - philo_i[0].time_to_die.tv_usec) / 1000);
}

int	ft_cnt_time_of_acti(t_philo *philo_i)
{
	gettimeofday(&philo_i[0].end, NULL);
	return ((philo_i[0].end.tv_usec - philo_i[0].start.tv_usec) / 1000);
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
		pthread_mutex_lock(philo_i[0].mutex_print);
		gettimeofday(&now, NULL);
		if (philo_i[0].die == 0)
			printf("%d %d %s\n", (now.tv_usec - begin->tv_usec) / 1000,
				philo_i[0].nbr, str);
		pthread_mutex_unlock(philo_i[0].mutex_print);
	}
	return (begin);
}
