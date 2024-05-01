/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:41:33 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 02:10:06 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

static void	ft_usage(void)
{
	printf("Please check input again. Input should follow following rules:");
	printf("\n   ./philo nbrber_of_philosophers du_to_die du_to_eat ");
	printf("du_to_sleep \n   [nbrber_of_times_each_philosopher_must_eat]");
	printf("\n   And they need to be given in miliseconds as well as need ");
	printf("to be meaningful.\n- The End -\n");
}

static int	ft_char_to_nbr(char *str)
{
	int	i;
	int	sum;

	if (str == 0)
		return (-1);
	sum = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-2);
		sum = (sum * 10) + (str[i] - '0');
	}
	return (sum);
}

static void	ft_sm_philo_set2(t_sm_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].sum)
	{
		philo[i].group_sum = philo[0].group_sum;
		philo[i].group = 1;
		if (i % 2 == 0)
			philo[i].group = 2;
		philo[i].die = 0;
		philo[i].ate_times = 0;
		philo[i].must_eat = philo[0].must_eat;
		philo[i].nbr = i;
		philo[i].sum = philo[0].sum;
		philo[i].du_die = philo[0].du_die;
		philo[i].du_eat = philo[0].du_eat;
		philo[i].du_sleep = philo[0].du_sleep;
		philo[i].sem_print = philo[0].sem_print;
	}
	philo[--i].group = philo[0].group_sum;
}

static int	ft_sm_philo_set(t_sm_philo *philo)
{
	philo[0].group_sum = 3;
	if (philo[0].sum % 2 == 0)
		philo[0].group_sum = 2;
	philo[0].group = philo[0].group_sum;
	philo[0].die = 0;
	ft_sm_philo_set2(philo);
}

//set everything, to it's value, but no mutex.
int	ft_sm_philo_fill(int ac, char **av, t_sm_philo *philo)
{
	int			philo_sum;

	if (ac < 5 || ac > 6)
		return (ft_usage(), NULL);
	philo_sum = ft_char_to_nbr(av[1]);
	if (philo_sum <= 0)
		return (0);
	philo[0].sum = philo_sum;
	philo[0].nbr = 0;
	philo[0].du_die = ft_char_to_nbr(av[2]);
	philo[0].du_eat = ft_char_to_nbr(av[3]);
	philo[0].du_sleep = ft_char_to_nbr(av[4]);
	philo[0].must_eat = ft_char_to_nbr(av[5]);
	if (philo[0].du_die < 0 || philo[0].du_eat < 0
		|| philo[0].du_sleep < 0 || philo[0].must_eat == -2)
		return (ft_usage(), 0);
	if (philo[0].must_eat == 0)
		return (1);
	ft_sm_philo_set(philo);
	return (1);
}
