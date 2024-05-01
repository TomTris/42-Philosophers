/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:59:09 by qdo               #+#    #+#             */
/*   Updated: 2024/05/01 03:00:57 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib_bonus.h"

//only for beginning time purpose
size_t	ft_begin(int check)
{
	struct timeval	begin_tv;
	static size_t	begin;

	if (check == 1)
	{
		gettimeofday(&begin_tv, 0);
		begin = (begin_tv.tv_sec * 1000) + (begin_tv.tv_usec / 1000);
	}
	return (begin);
}

//take current time
size_t	current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

//to malloc && mark child processes
void	ft_create_philos_pid_t(t_sm_philo *philo)
{
	philo->philos = (pid_t *)malloc((philo->sum + 1) * sizeof(pid_t));
	if (philo->philos == 0)
	{
		write(2, "malloc error\n", 13);
		ft_clean_programm(philo, 1);
	}
}

//kill to <i childprocess, exit with "check" value
void	ft_kill(t_sm_philo *philo, short i, char check)
{
	short	j;

	j = 0;
	while (++j < i)
		kill(philo->philos[i], SIGKILL);
	ft_clean_programm(philo, check);
}
