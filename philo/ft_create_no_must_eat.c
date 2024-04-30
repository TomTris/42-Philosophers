/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_no_must_eat.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:27 by qdo               #+#    #+#             */
/*   Updated: 2024/04/30 01:57:09 by qdo              ###   ########.fr       */
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

static size_t	ft_cnt_time_to_die(t_philo *philo_i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_usec - philo_i[0].time_to_die.tv_usec) / 1000)
		+ ((now.tv_sec - philo_i[0].time_to_die.tv_sec) * 1000));
}

static void	ft_print_n_set_die_super(t_philo *philo, int i_die)
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
static void	ft_check_die_super(t_philo *philo, int i, size_t time)
{
	while (++i <= philo[0].sum)
	{
		pthread_mutex_lock(&(philo[0].mutex_time_to_die[i].mutex));
		time = ft_cnt_time_to_die(&(philo[i]));
		if (time > (size_t) philo[0].time_die)
		{
			pthread_mutex_lock(philo[0].mutex_print);
			ft_print_n_set_die_super(philo, i);
			pthread_mutex_unlock((&philo[0].mutex_time_to_die[i].mutex));
			break ;
		}
		pthread_mutex_unlock((&philo[0].mutex_time_to_die[i].mutex));
		pthread_mutex_lock(&(philo[0].mutex_ate_times[0].mutex));
		if (philo[0].mutex_ate_times[0].nbr == philo[0].sum
			|| philo[0].mutex_ate_times[0].nbr < 0)
		{
			pthread_mutex_lock(philo[0].mutex_print);
			ft_print_n_set_die_super(philo, -1);
			pthread_mutex_unlock(&(philo[0].mutex_ate_times[0].mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo[0].mutex_ate_times[0].mutex));
		if (i == philo[0].sum)
			i = 0;
	}
}

int	ft_philo_create_no_must_eat(t_philo *philo, pthread_t *philo_id)
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
		pthread_create(&(philo_id[i]), NULL, (void *)&ft_philojob_no_must_eat,
			(void *)&(philo[i]));
	}
	ft_check_die_super(philo, 0, 0);
	i = 0;
	while (++i <= philo[0].sum)
		pthread_join(philo_id[i], NULL);
	free(begin);
	return (1);
}
