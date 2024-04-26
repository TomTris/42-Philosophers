/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:38:35 by qdo               #+#    #+#             */
/*   Updated: 2024/04/26 22:09:55 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

double	ft_time_count(t_philo *philo_i)
{
	gettimeofday(&philo_i->end, NULL);
	return ((philo_i->end.tv_usec - philo_i->start.tv_usec) / 1000);
}

void	ft_print_out(t_philo *philo_i, char *str)
{
	pthread_mutex_lock(philo_i->mutex_print);
	printf("%d %s", philo_i->nbr, str);
	pthread_mutex_unlock(philo_i->mutex_print);
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

void	ft_philo_job_alone(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	gettimeofday(&philo->start, NULL);
	ft_print_out(philo, "take a fork\n");
	usleep(philo->time_die);
	ft_print_out(philo, "die\n");
	philo->die = 1;
}

void	ft_creat_job(t_philo *philo, pthread_t *philo_id)
{
	int	i;
	int	philo_sum;
	int	j;

	philo_sum = philo[0].sum;
	while (++i <= philo_sum)
	{
		if (philo[i].die == 1)
		{
			j = 0;
			pthread_mutex_lock(philo[0].mutex_print);
			ft_print_out(&philo[i], "die\n");
			while (++j <= philo_sum)
				philo[j].die = 1;
			pthread_mutex_lock(philo[0].mutex_print);
		}
		if (i == philo_sum)
			i = 0;
	}
}

void	ft_philo_create(t_philo *philo, pthread_t *philo_id)
{
	int	i;

	if (philo[0].sum == 1)
		pthread_create(&philo_id[1], NULL, &ft_philo_job_alone,
			(void *)&philo[1]);
	else
		ft_create_job(philo, philo_id);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_t		*philo_id;

	philo_id = (pthread_t *)malloc((philo[0].nbr) + 1 * sizeof(pthread_t));
	if (philo_id == 0)
		return (1);
	philo = ft_philo_fill(ac, av);
	if (philo == 0)
		return (free(philo_id), 1);
	philo[0].psfork = ft_fork_fill(philo);
	if (philo[0].psfork == 0)
		return (free(philo_id), pthread_mutex_destroy(philo->mutex_die),
			pthread_mutex_destroy(philo->mutex_print), free(philo),
			free(philo->mutex_die), free(philo->mutex_print), 1);
	ft_philo_create(philo, philo_id);
	return (0);
}
