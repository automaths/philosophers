/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:51 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:02:50 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_forks(t_struct *philosopher)
{
	pthread_mutex_lock(&philosopher->first_fork);
	if (writing(philosopher, now(), DISPLAY_FIRST_FORK))
		return (true);
	pthread_mutex_lock(philosopher->second_fork);
	if (writing(philosopher, now(), DISPLAY_SECOND_FORK))
		return (true);
	return (false);
}

bool	eating(t_struct *philosopher)
{
	if (writing(philosopher, now(), DISPLAY_EATING))
		return (true);
	philosopher->ate = now();
	philosopher->times_ate++;
	if (chronometer(philosopher->infos[TIME_TO_EAT], philosopher, 2))
		return (true);
	pthread_mutex_unlock(&philosopher->first_fork);
	pthread_mutex_unlock(philosopher->second_fork);
	return (false);
}

bool	sleeping(t_struct *philosopher)
{
	if (writing(philosopher, now(), DISPLAY_SLEEPING))
		return (true);
	if (chronometer(philosopher->infos[TIME_TO_SLEEP], philosopher, 4))
		return (true);
	return (false);
}

bool	thinking(t_struct *philosopher)
{
	if (writing(philosopher, now(), DISPLAY_THINKING))
		return (true);
	while (now() - philosopher->ate < philosopher->infos[TIME_TO_DIE] * 0.75)
	{
		if (chronometer(10, philosopher, 4))
			return (true);
	}
	return (false);
}

void	*living(void *arg)
{
	t_struct	*philosopher;

	philosopher = (t_struct *)arg;
	while (now() < philosopher->synchronising)
		;
	if ((philosopher->number % 2) != 0)
		usleep(1000);
	while (1)
	{
		if (take_forks(philosopher))
			return (0);
		if (eating(philosopher))
			return (0);
		if (sleeping(philosopher))
			return (0);
		if (thinking(philosopher))
			return (0);
	}
	return (0);
}
