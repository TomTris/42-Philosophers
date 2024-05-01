/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:30:34 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 02:46:58 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

void	ft_clean_programm(t_sm_philo *philo, char check)
{
	close(philo->sem_fork);
	unlink("/sem_fork");
	close(philo->sem_print);
	unlink("/sem_print");
	close(philo->sem_print);
	unlink("/sem_print");
	close(philo->sem_ate_times);
	unlink("/sem_ate_times");
	exit(check);
}

static int	ft_set_sem(t_sm_philo *philo)
{
	sem_unlink("sem_ate_times");
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	philo->sem_ate_times = sem_open("/sem_ate_times",
			O_CREAT, 0644, philo->sum);
	if (philo->sem_ate_times == SEM_FAILED)
		return (0);
	philo->sem_fork = sem_open("/sem_fork", O_CREAT, 0644, philo->sum);
	if (philo->sem_fork == SEM_FAILED)
		return (close(philo->sem_ate_times), unlink("/sem_ate_times"), 0);
	philo->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (philo->sem_print == SEM_FAILED)
		return (close(philo->sem_fork), unlink("/sem_fork"),
			close(philo->sem_ate_times), unlink("/sem_ate_times"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_sm_philo	philo;

	if (ft_sm_philo_fill(ac, av, &philo) == 0)
		return (1);
	if (philo.must_eat == 0)
		return (0);
	if (ft_set_sem(&philo) == 0)
		return (1);
	if (ft_create_bonus(&philo) == 0)
		return (ft_clean_programm(&philo, EXIT_FAILURE), -99);
	return (ft_clean_programm(&philo, EXIT_SUCCESS), -99);
}
