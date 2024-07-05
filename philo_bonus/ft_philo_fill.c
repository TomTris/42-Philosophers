/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:41:33 by qdo               #+#    #+#             */
/*   Updated: 2024/07/05 14:56:04 by qdo              ###   ########.fr       */
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

	if (str == 0 || *str == 0)
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

//set everything, to it's value, but no mutex.
int	ft_sm_philo_fill(int ac, char **av, t_sm_philo *philo)
{
	int			philo_sum;

	if (ac < 5 || ac > 6)
		return (ft_usage(), exit(EXIT_FAILURE), -99);
	philo_sum = ft_char_to_nbr(av[1]);
	if (philo_sum <= 0)
		return (ft_usage(), exit(EXIT_FAILURE), -99);
	philo->sum = philo_sum;
	philo->nbr = 0;
	philo->du_die = ft_char_to_nbr(av[2]);
	philo->du_eat = ft_char_to_nbr(av[3]);
	philo->du_sleep = ft_char_to_nbr(av[4]);
	philo->must_eat = ft_char_to_nbr(av[5]);
	philo->ate_times = 0;
	if (philo->du_die < 0 || philo->du_eat < 0
		|| philo->du_sleep < 0 || philo->must_eat == -2)
		return (ft_usage(), exit(EXIT_FAILURE), -99);
	if (philo->must_eat == 0)
		return (exit(EXIT_SUCCESS), -99);
	philo->sem_ate_times = 0;
	philo->sem_fork = 0;
	philo->sem_fork_pair = 0;
	philo->sem_print = 0;
	philo->sem_super_prio = 0;
	return (philo->philos = 0, 1);
}
