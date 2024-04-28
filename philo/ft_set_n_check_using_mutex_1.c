/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_n_check_using_mutex_1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:10:07 by qdo               #+#    #+#             */
/*   Updated: 2024/04/28 13:23:15 by qdo              ###   ########.fr       */
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

int	ft_check_die(t_philo *philo_i)
{
	int	ret;

	pthread_mutex_lock(&philo_i[0].mutex_die[0].mutex);
	ret = philo_i[0].die;
	pthread_mutex_unlock(&philo_i[0].mutex_die[0].mutex);
	return (ret);
}

void	ft_print_n_set_die(t_philo *philo, int i_die)
{
	int	i;

	pthread_mutex_lock(philo[0].mutex_print);
	printf("%d die\n", i_die);
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
		if (ft_check_die(philo_i) == 0)
			printf("%ld %d %s\n",
				(((now.tv_sec - begin->tv_sec) * 1000)
					+ ((now.tv_usec - begin->tv_usec) / 1000)),
				philo_i[0].nbr, str);
		pthread_mutex_unlock(philo_i[0].mutex_print);
	}
	return (begin);
}
