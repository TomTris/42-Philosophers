/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_n_check_using_mutex_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:55 by qdo               #+#    #+#             */
/*   Updated: 2024/04/29 16:44:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

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
