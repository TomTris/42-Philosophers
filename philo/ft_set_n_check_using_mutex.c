/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_n_check_using_mutex.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:10:07 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 17:16:11 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_set_time_to_die(t_philo *philo_i)
{
	pthread_mutex_lock(&philo_i[0].mutex_time_to_die[0].mutex);
	pthread_mutex_lock(&philo_i[0].mutex_die[0].mutex);
	if (philo_i[0].die == 0 && ft_cnt_time_to_die(philo_i)
		< (size_t) philo_i[0].time_die)
		gettimeofday(&philo_i[0].time_to_die, NULL);
	pthread_mutex_unlock(&philo_i[0].mutex_die[0].mutex);
	pthread_mutex_unlock(&philo_i[0].mutex_time_to_die[0].mutex);
}

int	ft_check_die_philo(t_philo *philo_i)
{
	int			ret;

	ret = 0;
	pthread_mutex_lock(&philo_i[0].mutex_time_to_die[0].mutex);
	pthread_mutex_lock(&philo_i[0].mutex_die[0].mutex);
	if (philo_i[0].die == 1 || ft_cnt_time_to_die(philo_i)
		>= (size_t) philo_i[0].time_die)
		ret = 1;
	pthread_mutex_unlock(&philo_i[0].mutex_die[0].mutex);
	pthread_mutex_unlock(&philo_i[0].mutex_time_to_die[0].mutex);
	return (ret);
}

//ft_error(philo_i, 0) will set psfork[0].nbr = -1
// => supervisor always check psfork[0].nbr find out -> programm stop.
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
	}
	else if (philo_i != 0 && str != 0)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(philo_i[0].mutex_print);
		if (ft_check_die_philo(philo_i) == 0)
			if ((printf("%ld %d %s\n", (((now.tv_sec - begin->tv_sec) * 1000)
							+ ((now.tv_usec - begin->tv_usec) / 1000)),
						philo_i[0].nbr, str)) == -1)
				ft_error_report(philo_i);
		if (philo_i[0].nbr != 0)
			pthread_mutex_unlock(philo_i[0].mutex_print);
	}
	return (begin);
}

int	ft_check_ate_times(t_philo *philo_i)
{
	int	ret;

	pthread_mutex_lock(&philo_i[0].mutex_ate_times[0].mutex);
	ret = philo_i[0].mutex_ate_times[0].nbr;
	pthread_mutex_unlock(&philo_i[0].mutex_ate_times[0].mutex);
	return (ret);
}

void	ft_set_ate_times(t_philo *philo_i)
{
	pthread_mutex_lock(&philo_i[0].mutex_ate_times[0].mutex);
	++(philo_i[0].mutex_ate_times[0].nbr);
	pthread_mutex_unlock(&philo_i[0].mutex_ate_times[0].mutex);
}
