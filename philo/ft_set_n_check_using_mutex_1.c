/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_n_check_using_mutex_1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:10:07 by qdo               #+#    #+#             */
/*   Updated: 2024/04/28 17:38:10 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

void	ft_set_time_to_die(t_philo *philo_i)
{
	pthread_mutex_lock(&philo_i[0].mutex_time_to_die[0].mutex);
	pthread_mutex_lock(&philo_i[0].mutex_die[0].mutex);
	if (philo_i[0].die == 0)
		gettimeofday(&philo_i[0].time_to_die, NULL);
	pthread_mutex_unlock(&philo_i[0].mutex_die[0].mutex);
	pthread_mutex_unlock(&philo_i[0].mutex_time_to_die[0].mutex);
}

long int	ft_cnt_time_to_die(t_philo *philo_i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_usec - philo_i[0].time_to_die.tv_usec) / 1000)
		+ ((now.tv_sec - philo_i[0].time_to_die.tv_sec) * 1000));
}

int	ft_check_die_philo(t_philo *philo_i)
{
	int			ret;

	ret = 0;
	pthread_mutex_lock(&philo_i[0].mutex_time_to_die[0].mutex);
	pthread_mutex_lock(&philo_i[0].mutex_die[0].mutex);
	if (philo_i[0].die == 1)
		ret = 1;
	else if (ft_cnt_time_to_die(philo_i) > philo_i[0].time_die)
	{
		philo_i[0].die = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&philo_i[0].mutex_die[0].mutex);
	pthread_mutex_unlock(&philo_i[0].mutex_time_to_die[0].mutex);
	return (ret);
}


//a philo, after eating need to check time if he's still alive, how? checkft_cnt_time_to_die
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
		if (ft_check_die_philo(philo_i) == 0)
			printf("%ld %d %s\n",
				(((now.tv_sec - begin->tv_sec) * 1000)
					+ ((now.tv_usec - begin->tv_usec) / 1000)),
				philo_i[0].nbr, str);
		pthread_mutex_unlock(philo_i[0].mutex_print);
	}
	return (begin);
}
