/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:03:28 by qdo               #+#    #+#             */
/*   Updated: 2024/04/26 21:33:59 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

static void	ft_usage(void)
{
	printf("Please check input again. Input should follow following rules:");
	printf("\n   ./philo nbrber_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep \n   [nbrber_of_times_each_philosopher_must_eat]");
	printf("\n   And they need to be given in miliseconds as well as need ");
	printf("to be meaningful.\n- The End -\n");
}

static int	ft_char_to_nbr(char *str)
{
	int	i;
	int	sum;

	i = 0;
	if (str == 0)
		return (-1);
	sum = 0;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-2);
		sum = (sum * 10) + (str[i] - '0');
	}
	return (sum);
}

static void	ft_philo_set2(t_philo *philo, int group)
{
	int				i;

	if (philo[0].nbr % 2 == 0)
		group = 2;
	i = 0;
	while (++i <= philo[0].nbr)
	{
		philo[i].die = 0;
		philo[i].ate_times = 0;
		philo[i].must_eat = philo[0].must_eat;
		philo[i].nbr = i;
		philo[i].sum = philo[0].sum;
		philo[i].time_die = philo[0].time_die;
		philo[i].time_eat = philo[0].time_eat;
		philo[i].time_sleep = philo[0].time_sleep;
		philo[i].group = 1;
		philo[i].mutex_die = philo[0].mutex_die;
		philo[i].mutex_print = philo[0].mutex_print;
		if (i % 2 == 0)
			philo[i].group = 2;
	}
	if (group == 3)
		philo[--i].group = 3;
	philo[0].die = 0;
}

static int	ft_philo_set(t_philo *philo)
{
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_die;

	mutex_print = (pthread_mutex_t *)malloc(2 * sizeof(pthread_mutex_t));
	if (mutex_print == 0)
		return (0);
	mutex_die = (pthread_mutex_t *)malloc(2 * sizeof(pthread_mutex_t));
	if (mutex_die == 0)
		return (free(mutex_print), 0);
	pthread_mutex_init(mutex_print, NULL);
	pthread_mutex_init(mutex_die, NULL);
	ft_philo_set2(philo, 3);
	return (1);
}


t_philo	*ft_philo_fill(int ac, char **av)
{
	t_philo	*philo;
	int		philo_sum;

	if (ac < 5 || ac > 6)
		ft_usage();
	philo_sum = ft_char_to_nbr(av[1]);
	if (philo_sum < 0)
		return (0);
	philo = (t_philo *)malloc((philo_sum + 1) * sizeof(t_philo));
	if (philo == 0)
		return (0);
	philo[0].sum = philo_sum;
	philo[0].nbr = philo_sum;
	philo[0].time_die = ft_char_to_nbr(av[2]);
	philo[0].time_eat = ft_char_to_nbr(av[3]);
	philo[0].time_sleep = ft_char_to_nbr(av[4]);
	philo[0].must_eat = ft_char_to_nbr(av[5]);
	if (philo[0].time_die < 0 || philo[0].time_eat < 0
		|| philo[0].time_sleep < 0)
		return (free(philo), ft_usage(), NULL);
	if (philo[0].must_eat == -2)
		return (free(philo), NULL);
	if (ft_philo_set(philo) == 0)
		return (free(philo), NULL);
	return (philo);
}
