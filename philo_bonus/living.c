/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:31 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:07:09 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_struct *philosopher)
{
	check_death(philosopher, DISPLAY_SLEEPING);
	sem_wait(philosopher->common_forks);
	writing(philosopher, now(), DISPLAY_FIRST_FORK);
	sem_wait(philosopher->common_forks);
	writing(philosopher, now(), DISPLAY_SECOND_FORK);
}

void	eating(t_struct *philosopher)
{
	writing(philosopher, now(), DISPLAY_EATING);
	philosopher->ate = now();
	philosopher->times_ate++;
	chronometer(philosopher->infos[TIME_TO_EAT], philosopher, DISPLAY_EATING);
	sem_post(philosopher->common_forks);
	sem_post(philosopher->common_forks);
}

void	sleeping(t_struct *philosopher)
{
	writing(philosopher, now(), DISPLAY_SLEEPING);
	chronometer(philosopher->infos[TIME_TO_SLEEP], philosopher, 0);
}

void	thinking(t_struct *philosopher)
{
	writing(philosopher, now(), DISPLAY_THINKING);
	while (now() - philosopher->ate < philosopher->infos[TIME_TO_DIE] * 0.75)
		chronometer(10, philosopher, 0);
}

void	*living(t_struct *philosopher)
{
	while (now() < philosopher->synchronising)
		;
	if ((philosopher->number % 2) != 0)
		usleep(1000);
	while (1)
	{
		take_forks(philosopher);
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	exit (0);
}
