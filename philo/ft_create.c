/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:27 by qdo               #+#    #+#             */
/*   Updated: 2024/04/29 14:45:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_philo_job_alone(void *param)
{
	t_philo				*philo_1;
	long int			time_cnt;
	struct timeval		now;

	philo_1 = (t_philo *)param;
	gettimeofday(&philo_1[0].start, NULL);
	pthread_mutex_lock(&philo_1[0].psfork[1].mutex);
	printf("0 1 took a fork\n");
	printf("--%d \n", philo_1[0].time_die);
	while (1)
	{
		gettimeofday(&now, NULL);
		time_cnt = (now.tv_usec - philo_1[0].start.tv_usec) / 1000
			+ (now.tv_sec - philo_1[0].start.tv_sec) * 1000;
		printf("%ld\n", time_cnt);
		if (time_cnt >= philo_1[0].time_die)
		{
			printf("%ld 1 die\n", time_cnt);
			pthread_mutex_unlock(&philo_1[0].psfork[1].mutex);
			break ;
		}
	}
}

static void	ft_print_n_set_die_super(t_philo *philo, int i_die)
{
	int				i;
	struct timeval	*begin;
	struct timeval	now;

	begin = ft_print_out(NULL, NULL);
	gettimeofday(&now, NULL);
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

static void	ft_check_die_super(t_philo *philo)
{
	int		i;
	double	time;

	i = 0;
	while (++i <= philo[0].sum)
	{
		pthread_mutex_lock(&(philo[0].mutex_time_to_die[i].mutex));
		time = ft_cnt_time_to_die(&(philo[i]));
		if (time > (double) philo[0].time_die)
		{
			pthread_mutex_lock(philo[0].mutex_print);
			ft_print_n_set_die_super(philo, i);
			pthread_mutex_unlock(&(philo[0].mutex_time_to_die[i].mutex));
			break ;
		}
		pthread_mutex_unlock((&philo[0].mutex_time_to_die[i].mutex));
		if (i == philo[0].sum)
			i = 0;
	}
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
	ft_check_die_super(philo);
	i = 0;
	while (++i <= philo[0].sum)
		pthread_join(philo_id[i], NULL);
	// printf("hiere is after pthread join\n");
	free(begin);
	return (1);
}

// static void	ft_philo(t_philo *philo)
// {
// 	int	i;

// 	i = -1;
// 	while (++i <= philo[0].sum)
// 	{
// 		printf("philo[%d].ate_time = %d\n",i, philo[i].ate_times);
// 		printf("philo[%d].die = %d\n",i, philo[i].die);
// 		printf("philo[%d].group = %d\n",i, philo[i].group);
// 		printf("philo[%d].group_sum = %d\n",i, philo[i].group_sum);
// 		printf("philo[%d].must eat = %d\n",i, philo[i].must_eat);
// 		printf("philo[%d]. print= %p\n",i, philo[i].mutex_print);
// 		printf("philo[%d].nbr = %d\n",i, philo[i].nbr);
// 		printf("philo[%d].sum = %d\n",i, philo[i].sum);
// 		printf("philo[%d].tdie = %d\n",i, philo[i].time_die);
// 		printf("philo[%d].teat = %d\n",i, philo[i].time_eat);
// 		printf("philo[%d].tsleep = %d\n",i, philo[i].time_sleep);
// 	}
// }