/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:27 by qdo               #+#    #+#             */
/*   Updated: 2024/04/27 14:02:56 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_philo_job_alone(void *param)
{
	t_philo				*philo_1;
	long int			time_cnt;

	philo_1 = (t_philo *)param;
	gettimeofday(&philo_1[0].start, NULL);
	pthread_mutex_lock(&philo_1[0].psfork[1].mutex);
	printf("0 1 took a fork\n");
	while (1)
	{
		gettimeofday(&philo_1[0].end, NULL);
		time_cnt = (philo_1[0].end.tv_usec - philo_1[0].start.tv_usec) / 1000
			+ (philo_1[0].end.tv_sec - philo_1[0].start.tv_sec) * 1000;
		printf("%ld\n", time_cnt);
		if (time_cnt >= philo_1[0].time_die)
		{
			printf("%ld 1 die\n", time_cnt);
			pthread_mutex_unlock(&philo_1[0].psfork[1].mutex);
			break ;
		}
	}
}

static void	ft_check_die(t_philo *philo, int philo_sum)
{
	int				i;
	int				j;
	struct timeval	now;
	struct timeval	*begin;

	i = 0;
	while (++i <= philo_sum)
	{
		if (philo[i].die == 1)
		{
			pthread_mutex_lock(philo[0].mutex_print);
			gettimeofday(&now, NULL);
			begin = ft_print_out(NULL, NULL);
			printf("%d %d %s", (now.tv_usec - begin->tv_usec) / 1000,
				philo[i].nbr, "die\n");
			j = 0;
			while (++j <= philo_sum)
				philo[j].die = 1;
			pthread_mutex_unlock(philo[0].mutex_print);
			break ;
		}
		else if (i == philo_sum)
			i = 0;
	}
}

static void	ft_philo_job(void *philo_data)
{
	t_philo			*philo_i;
	struct timeval	*begin;

	philo_i = (t_philo *)philo_data;
	begin = ft_print_out(NULL, NULL);
	philo_i[0].time_to_die = *begin;
	if (philo_i[0].group_sum == 2)
		ft_philojob_groupsum2(philo_i);
	else
		ft_philojob_groupsum3(philo_i);
}

void	ft_philo_create(t_philo *philo, pthread_t *philo_id)
{
	int				i;
	struct timeval	*begin;
	if (philo[0].sum == 1)
	{
		pthread_create(&philo_id[1], NULL, (void *)&ft_philo_job_alone,
			(void *)&philo[1]);
		pthread_join(philo_id[1], NULL);
		printf("5\n");
	}
	else
	{
		i = 0;
		begin = ft_print_out(NULL, NULL);
		if (begin == NULL)
			return ;
		while (++i <= philo[0].sum)
			pthread_create(&philo_id[i], NULL, (void *)&ft_philo_job,
				(void *)&philo[i]);
		ft_check_die(philo, philo[0].sum);
		i = 0;
		while (++i <= philo[0].nbr)
			pthread_join(philo_id[i], NULL);
		free(begin);
	}
}