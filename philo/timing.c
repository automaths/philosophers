/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:00 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:03:05 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	now(void)
{
	struct timeval	since_epoch;

	gettimeofday(&since_epoch, NULL);
	return ((since_epoch.tv_sec * 1000) + (since_epoch.tv_usec / 1000));
}

bool	chronometer(time_t time, t_struct *philosopher, int type)
{
	time_t	stop;
	int		i;

	stop = now() + time;
	i = -1;
	while (now() < stop)
	{
		usleep(100);
		if (++i == 10)
		{
			if (check_death(philosopher, type))
				return (true);
			if (check_meals(philosopher, type))
				return (true);
			i = -1;
		}
	}
	return (false);
}
