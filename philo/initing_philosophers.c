/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:48 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:02:44 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_end(t_global *dining)
{
	pthread_mutex_lock(&dining->muerte);
	if (dining->el_muerte == 1)
	{
		pthread_mutex_unlock(&dining->muerte);
		return (true);
	}
	pthread_mutex_unlock(&dining->muerte);
	pthread_mutex_lock(&dining->full_bellies);
	if (dining->el_full_bellies == 1)
	{
		pthread_mutex_unlock(&dining->full_bellies);
		return (true);
	}
	pthread_mutex_unlock(&dining->full_bellies);
	return (false);
}

bool	give_birth(t_global *dining)
{
	int		i;
	int		ret;
	int		end;
	void	*ptr;

	i = -1;
	while (++i < dining->infos[NB_PHILOSOPHERS])
	{
		dining->philosophers[i].synchronising = now() + 1000;
		dining->philosophers[i].birth = now() + 1000;
		ptr = &dining->philosophers[i];
		ret = pthread_create(&dining->philosophers[i].living, 0, living, ptr);
		if (ret)
			return (erroring(ret, ERROR_THREAD_CREATE), false);
	}
	end = 1;
	while (end)
	{
		if (check_end(dining))
			end = 0;
		sleep(1);
	}
	return (true);
}

bool	give_second_fork(t_global *dining)
{
	int	i;

	i = 0;
	while (++i < dining->infos[NB_PHILOSOPHERS])
		dining->philosophers[i].second_fork = \
			&dining->philosophers[i - 1].first_fork;
	dining->philosophers[0].second_fork = \
		&dining->philosophers[dining->infos[NB_PHILOSOPHERS] - 1].first_fork;
	return (true);
}

void	assign_philo_infos(t_global *dining)
{
	int	i;

	i = -1;
	while (++i < dining->infos[NB_PHILOSOPHERS])
	{
		dining->philosophers[i].infos[NB_PHILOSOPHERS] = \
			dining->infos[NB_PHILOSOPHERS];
		dining->philosophers[i].infos[TIME_TO_DIE] = dining->infos[TIME_TO_DIE];
		dining->philosophers[i].infos[TIME_TO_EAT] = dining->infos[TIME_TO_EAT];
		dining->philosophers[i].infos[TIME_TO_SLEEP] = \
			dining->infos[TIME_TO_SLEEP];
		dining->philosophers[i].infos[TARGET_MEALS] = \
			dining->infos[TARGET_MEALS];
		dining->philosophers[i].number = i;
		dining->philosophers[i].writing = &dining->writing;
		dining->philosophers[i].ate = now() + 1000;
		dining->philosophers[i].times_ate = 0;
		dining->philosophers[i].muerte = &dining->muerte;
		dining->philosophers[i].full_bellies = &dining->full_bellies;
		dining->philosophers[i].el_muerte = &dining->el_muerte;
		dining->philosophers[i].el_full_bellies = &dining->el_full_bellies;
	}	
}

bool	initing_philosophers(t_global *dining)
{
	int	ret;
	int	i;

	dining->philosophers = (t_struct *)malloc(sizeof(t_struct) * \
		dining->infos[NB_PHILOSOPHERS]);
	if (dining->philosophers == NULL)
		return (write(1, "a problem occured during malloc, exiting\n", \
			ft_strlen("a problem occured during malloc, exiting\n")));
	i = -1;
	while (++i < dining->infos[NB_PHILOSOPHERS])
	{
		ret = pthread_mutex_init(&dining->philosophers[i].first_fork, NULL);
		if (ret != 0)
			return (erroring(ret, ERROR_MUTEX_CREATE), false);
	}
	assign_philo_infos(dining);
	if (!give_second_fork(dining))
		return (false);
	if (!give_birth(dining))
		return (false);
	return (true);
}
