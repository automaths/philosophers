/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:28 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:07:04 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	give_birth(t_global *dining)
{
	int	i;
	int	end;

	i = -1;
	while (++i < dining->infos[NB_PHILOSOPHERS])
	{
		dining->philosophers[i].synchronising = now() + 1000;
		dining->philosophers[i].birth = now() + 1000;
		dining->philosophers[i].pid = fork();
		if (dining->philosophers[i].pid == 0)
			living(&dining->philosophers[i]);
		else if (dining->philosophers[i].pid == -1)
			return (erroring(0, ERROR_FORK_CREATE), false);
	}
	waitpid(-1, &end, 0);
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
		dining->philosophers[i].common_forks = dining->common_forks;
		dining->philosophers[i].writing = dining->writing;
		dining->philosophers[i].ate = now() + 1000;
		dining->philosophers[i].times_ate = 0;
	}	
}

bool	initing_philosophers(t_global *dining)
{
	dining->philosophers = (t_struct *)malloc(sizeof(t_struct) * \
		dining->infos[NB_PHILOSOPHERS]);
	if (dining->philosophers == NULL)
		return (write(1, "a problem occured during malloc, exiting\n", \
			ft_strlen("a problem occured during malloc, exiting\n")), false);
	assign_philo_infos(dining);
	if (!give_birth(dining))
		return (false);
	return (true);
}
