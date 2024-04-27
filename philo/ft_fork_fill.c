/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:07:21 by qdo               #+#    #+#             */
/*   Updated: 2024/04/27 13:19:41 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philolib.h"

t_fork_mutex	*ft_fork_fill(t_philo *philo)
{
	t_fork_mutex	*psfork;
	int				i;

	psfork = (t_fork_mutex *)malloc((philo[0].nbr + 1) * sizeof(t_fork_mutex));
	if (psfork == 0)
		return (0);
	psfork[0].nbr = philo[0].nbr;
	philo[0].psfork = psfork;
	i = 0;
	while (++i <= philo[0].nbr)
	{
		philo[i].psfork = philo[0].psfork;
		pthread_mutex_init(&psfork[i].mutex, NULL);
		psfork[i].nbr = i;
		psfork[i].used = philo[0].group;
	}
	return (psfork);
}
