/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:36:27 by qdo               #+#    #+#             */
/*   Updated: 2024/04/26 23:00:02 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_philo_job_alone(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	printf("0 1 took a fork\n");
	usleep(philo->time_die);
	printf("%d 1 die\n", philo->time_die);
}

static void	ft_check_die(t_philo *philo, int philo_sum)
{
	int				i;
	int				j;
	struct timeval	now;
	struct timeval	*begin;

	while (++i <= philo_sum)
	{
		if (philo[i].die == 1)
		{
			j = 0;
			pthread_mutex_lock(philo[0].mutex_print);
			gettimeofday(&now, NULL);
			begin = ft_print_out(NULL, NULL);
			printf("%d %d %s", (now.tv_usec - begin->tv_usec) / 1000,
				philo[i].nbr, "die\n");
			while (++j <= philo_sum)
				philo[j].die = 1;
			free(begin);
			pthread_mutex_unlock(philo[0].mutex_print);
			break ;
		}
		else if (i == philo_sum)
			i = 0;
	}
}

void	ft_philo_job(void *philo_data)
{
	t_philo	*philo_i;
	double	time_cnt;

	philo_i = (t_philo *)philo_data;
	gettimeofday(&philo_i->start, NULL);
	if ((philo_i->group == 1 && philo_i->psfork[0].used == philo_i->group)
		|| )
	{
		pthread_mutex_lock(&philo_i->psfork[philo_i->nbr].mutex);
		ft_print_out(philo_i, "took left fork\n");
		if (philo_i->nbr == philo_i->sum)
			pthread_mutex_lock(&philo_i->psfork[1].mutex);
		else
			pthread_mutex_lock(&philo_i->psfork[philo_i->nbr + 1].mutex);
		ft_print_out(philo_i, "took right fork\n");
		ft_print_out(philo_i, "is eating\n");
		usleep(philo_i->time_eat * 1000 / 2);
		time_cnt = ft_time_count(philo_i);
		while (time_cnt < philo_i->time_eat - 100)
			usleep((philo_i->time_eat * 1000 - time_cnt) / 2);
		if (ft_time_count(philo_i) < philo_i->time_eat)
			time_cnt = 0;
	}
}

void	ft_philo_create(t_philo *philo, pthread_t *philo_id)
{
	int	i;

	if (philo[0].sum == 1)
		pthread_create(&philo_id[1], NULL, &ft_philo_job_alone,
			(void *)&philo[1]);
	else
	{
		i = 0;
		while (++i <= philo[0].sum)
			pthread_create(&philo_id[i], NULL, &ft_philo_job,
				(void *)&philo[i]);
		ft_check_die(philo, philo[0].sum);
	}
}
