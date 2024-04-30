/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:55 by qdo               #+#    #+#             */
/*   Updated: 2024/04/30 22:47:20 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static int	ft_philo_job_alone(void *param)
{
	t_philo				*philo_1;
	long int			time_cnt;
	struct timeval		now;

	philo_1 = (t_philo *)param;
	gettimeofday(&philo_1[0].start, NULL);
	pthread_mutex_lock(&philo_1[0].psfork[1].mutex);
	if (printf("0 1 took a fork\n") == -1)
		return (write(2, "printf error\n", 13), 0);
	while (1)
	{
		gettimeofday(&now, NULL);
		time_cnt = (now.tv_usec - philo_1[0].start.tv_usec) / 1000
			+ (now.tv_sec - philo_1[0].start.tv_sec) * 1000;
		if (time_cnt >= philo_1[0].time_die)
		{
			if (printf("%ld 1 die\n", time_cnt) == -1)
				return (write(2, "printf error\n", 13), 0);
			pthread_mutex_unlock(&philo_1[0].psfork[1].mutex);
			break ;
		}
	}
	return (1);
}

int	ft_philo_create(t_philo *philo, pthread_t *philo_id)
{
	int				i;
	struct timeval	*begin;

	if (philo[0].sum == 1)
	{
		pthread_create(&philo_id[1], NULL, (void *)&ft_philo_job_alone,
			(void *)&philo[1]);
		return (pthread_join(philo_id[1], NULL), 1);
	}
	begin = ft_print_out(NULL, NULL);
	if (begin == NULL)
		return (0);
	i = 0;
	while (++i <= philo[0].sum)
	{
		philo[i].time_to_die = *begin;
		pthread_create(&(philo_id[i]), NULL, (void *)&ft_philojob,
			(void *)&(philo[i]));
	}
	ft_check_die_super(philo, 0, 0);
	i = 0;
	while (++i <= philo[0].sum)
		pthread_join(philo_id[i], NULL);
	free(begin);
	return (1);
}
