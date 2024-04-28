/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_n_check_using_mutex_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:55 by qdo               #+#    #+#             */
/*   Updated: 2024/04/28 23:32:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

// void	ft_set_start_time(t_philo *philo_i)
// {
// 	pthread_mutex_lock(&philo_i[0].mutex_start[0].mutex);
// 	gettimeofday(&philo_i[0].start, NULL);
// 	pthread_mutex_unlock(&philo_i[0].mutex_start[0].mutex);
// }

// double	ft_cnt_time_of_acti(t_philo *philo_i)
// {
// 	struct timeval	now;
// 	double			time;

// 	pthread_mutex_lock(&philo_i[0].mutex_start[0].mutex);
// 	gettimeofday(&now, NULL);
// 	time = ((now.tv_usec - philo_i[0].start.tv_usec) / 1000)
// 		+ ((now.tv_sec - philo_i[0].start.tv_sec) * 1000);
// 	pthread_mutex_unlock(&philo_i[0].mutex_start[0].mutex);
// 	return (time);
// }

int	ft_check_ate_times(t_philo *philo_i)
{
	int	ret;

	pthread_mutex_lock(&philo_i[0].mutex_ate_times[0].mutex);
	ret = philo_i[0].ate_times;
	pthread_mutex_unlock(&philo_i[0].mutex_ate_times[0].mutex);
	return (ret);
}

void	ft_set_ate_times(t_philo *philo_i)
{
	pthread_mutex_lock(&philo_i[0].mutex_ate_times[0].mutex);
	philo_i[0].mutex_ate_times++;
	pthread_mutex_unlock(&philo_i[0].mutex_ate_times[0].mutex);
}
