/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:36:27 by qdo               #+#    #+#             */
/*   Updated: 2024/04/30 22:44:39 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_print_n_set_die_super(t_philo *philo, int i_die)
{
	int				i;
	struct timeval	*begin;
	struct timeval	now;

	begin = ft_print_out(NULL, NULL);
	gettimeofday(&now, NULL);
	if (i_die > 0)
		printf("%ld %d die\n", ((now.tv_sec - begin->tv_sec) * 1000)
			+ ((now.tv_usec - begin->tv_usec) / 1000), i_die);
	i = 0;
	while (++i <= philo[0].sum)
		pthread_mutex_lock(&philo[i].mutex_die[0].mutex);
	i = 0;
	while (++i <= philo[0].sum)
	{
		philo[i].die = 1;
		pthread_mutex_unlock(&philo[i].mutex_die[0].mutex);
	}
	pthread_mutex_unlock(philo[0].mutex_print);
}

//if (mutex_time_to_die == -1) => that philo set itself
//to report error of print func.
void	ft_check_die_super(t_philo *philo, int i, size_t time)
{
	while (++i <= philo[0].sum)
	{
		pthread_mutex_lock(&(philo[0].mutex_time_to_die[i].mutex));
		time = ft_cnt_time_to_die(&(philo[i]));
		if (time >= (size_t) philo[0].time_die)
		{
			pthread_mutex_unlock((&philo[0].mutex_time_to_die[i].mutex));
			pthread_mutex_lock(philo[0].mutex_print);
			ft_print_n_set_die_super(philo, i);
			break ;
		}
		pthread_mutex_unlock((&philo[0].mutex_time_to_die[i].mutex));
		pthread_mutex_lock(&(philo[0].mutex_ate_times[0].mutex));
		if (philo[0].mutex_ate_times[0].nbr == philo[0].sum
			|| philo[0].mutex_ate_times[0].nbr < 0)
		{
			pthread_mutex_unlock(&(philo[0].mutex_ate_times[0].mutex));
			pthread_mutex_lock(philo[0].mutex_print);
			ft_print_n_set_die_super(philo, -1);
			break ;
		}
		pthread_mutex_unlock(&(philo[0].mutex_ate_times[0].mutex));
		if (i == philo[0].sum)
			i = 0;
	}
}

size_t	ft_cnt_time_to_die(t_philo *philo_i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_usec - philo_i[0].time_to_die.tv_usec) / 1000)
		+ ((now.tv_sec - philo_i[0].time_to_die.tv_sec) * 1000));
}
