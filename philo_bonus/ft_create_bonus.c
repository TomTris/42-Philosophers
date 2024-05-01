/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:27:25 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 03:04:06 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

void	ft_parent_job(t_sm_philo *philo)
{
	short	i;
	int		status;

	i = 0;
	while (++i <= philo->sum)
	{
		waitpid(-1, &status, 0);
		if ()
	}
}

int	ft_create_bonus(t_sm_philo *philo)
{
	int		i;

	ft_create_philos_pid_t(philo);
	i = 0;
	while (++i <= philo->sum)
	{
		philo->philos[i] = fork();
		if (philo->philos[i] < 0)
		{
			write(2, "fork error\n", 11);
			ft_kill(philo, i, EXIT_FAILURE);
		}
		if (philo->philos[i] == 0)
		{
			philo->nbr = i;
			ft_ms_philojob(philo);
			exit(EXIT_SUCCESS);
		}
	}
	ft_parent_job(philo);
	return (1);
}
