/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_n_check_using_mutex_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:55 by qdo               #+#    #+#             */
/*   Updated: 2024/04/28 13:22:56 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_set_start_time(t_philo *philo_i)
{
	pthread_mutex_lock(&philo_i[0].mutex_start[0].mutex);
	gettimeofday(&philo_i[0].start, NULL);
	pthread_mutex_unlock(&philo_i[0].mutex_start[0].mutex);
}

long int	ft_cnt_time_of_acti(t_philo *philo_i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_usec - philo_i[0].start.tv_usec) / 1000)
		+ (now.tv_sec - philo_i[0].start.tv_sec) * 1000);
}

void	ft_set_time_to_die(t_philo *philo_i)
{
	pthread_mutex_lock(&philo_i[0].mutex_time_to_die[0].mutex);
	gettimeofday(&philo_i[0].time_to_die, NULL);
	pthread_mutex_unlock(&philo_i[0].mutex_time_to_die[0].mutex);
}

long int	ft_cnt_time_to_die(t_philo *philo_i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_usec - philo_i[0].time_to_die.tv_usec) / 1000)
		+ ((now.tv_sec - philo_i[0].time_to_die.tv_sec) * 1000));
}
