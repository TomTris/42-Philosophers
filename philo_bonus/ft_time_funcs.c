/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:59:09 by qdo               #+#    #+#             */
/*   Updated: 2024/05/02 12:33:49 by qdo              ###   ########.fr       */
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
		begin = (begin_tv.tv_sec * 1000000) + (begin_tv.tv_usec);
	}
	return (begin);
}

//take current time
size_t	ft_current_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return ((current.tv_sec * 1000000) + (current.tv_usec));
}
