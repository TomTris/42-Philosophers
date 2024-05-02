/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:30:34 by qdo               #+#    #+#             */
/*   Updated: 2024/05/02 19:31:09 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

void	ft_clean_programm(t_sm_philo *philo, char check)
{
	sem_close(philo->sem_ate_times);
	unlink("/sem_ate_times");
	if (philo->sem_fork != 0 && philo->sem_fork != SEM_FAILED)
	{
		sem_close(philo->sem_fork);
		unlink("/sem_fork");
	}
	if (philo->sem_print != 0 && philo->sem_print != SEM_FAILED)
	{
		sem_close(philo->sem_print);
		unlink("/sem_print");
	}
	if (philo->sem_super_prio != 0 && philo->sem_super_prio != SEM_FAILED)
	{
		sem_close(philo->sem_super_prio);
		unlink("/sem_super_prio");
	}
	if (philo->sem_fork_pair != 0 && philo->sem_fork_pair != SEM_FAILED)
	{
		sem_close(philo->sem_fork_pair);
		unlink("/sem_fork_pair");
	}
	if (philo->philos != 0)
		free(philo->philos);
	exit(check);
}

static int	ft_set_sem(t_sm_philo *philo)
{
	sem_unlink("/sem_ate_times");
	philo->sem_ate_times = sem_open("/sem_ate_times",
			O_CREAT, 0666, 0);
	if (philo->sem_ate_times == SEM_FAILED)
		return (0);
	sem_unlink("/sem_fork");
	philo->sem_fork = sem_open("/sem_fork", O_CREAT, 0666, philo->sum);
	if (philo->sem_fork == SEM_FAILED)
		return (ft_clean_programm(philo, EXIT_FAILURE), -99);
	sem_unlink("/sem_print");
	philo->sem_print = sem_open("/sem_print", O_CREAT, 0666, 1);
	if (philo->sem_print == SEM_FAILED)
		return (ft_clean_programm(philo, EXIT_FAILURE), -99);
	sem_unlink("/sem_super_prio");
	philo->sem_super_prio = sem_open("/sem_super_prio", O_CREAT, 0666, 1);
	if (philo->sem_super_prio == SEM_FAILED)
		return (ft_clean_programm(philo, EXIT_FAILURE), -99);
	sem_unlink("/sem_fork_pair");
	philo->sem_fork_pair = sem_open("/sem_fork_pair", O_CREAT,
			0666, philo->sum / 2);
	if (philo->sem_fork_pair == SEM_FAILED)
		return (ft_clean_programm(philo, EXIT_FAILURE), -99);
	return (1);
}

static void	ft_alone(t_sm_philo *philo)
{
	pid_t			child;

	child = fork();
	if (child < 0)
		ft_clean_programm(philo, EXIT_FAILURE);
	else if (child == 0)
	{
		ft_begin(1);
		printf("%ld 1 is thinking\n", (ft_current_time() - ft_begin(0)) / 1000);
		printf("%ld 1 has taken a fork\n",
			(ft_current_time() - ft_begin(0)) / 1000);
		while (1)
		{
			if (ft_current_time() - ft_begin(0)
				>= (size_t) philo->du_die * 1000)
			{
				printf("%ld 1 died\n",
					(ft_current_time() - ft_begin(0)) / 1000);
				exit(EXIT_FAILURE);
			}
		}
	}
	waitpid(-1, 0, 0);
	ft_clean_programm(philo, EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_sm_philo	philo;

	ft_sm_philo_fill(ac, av, &philo);
	if (ft_set_sem(&philo) == 0)
		return (1);
	if (philo.sum == 1)
		ft_alone(&philo);
	ft_create_bonus(&philo);
}
