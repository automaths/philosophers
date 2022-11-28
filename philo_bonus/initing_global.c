/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_global.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:12 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:07:00 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	initing_global(t_global *dining, int argc, char **argv)
{
	dining->infos[NB_PHILOSOPHERS] = ft_atoi(argv[1]);
	dining->infos[TIME_TO_DIE] = ft_atoi(argv[2]);
	dining->infos[TIME_TO_EAT] = ft_atoi(argv[3]);
	dining->infos[TIME_TO_SLEEP] = ft_atoi(argv[4]);
	if (argc == 6)
		dining->infos[TARGET_MEALS] = ft_atoi(argv[5]);
	else
		dining->infos[TARGET_MEALS] = -1;
	sem_unlink("first");
	sem_unlink("second");
	dining->common_forks = sem_open("first", O_CREAT, 0660, \
		dining->infos[NB_PHILOSOPHERS]);
	if (dining->common_forks == SEM_FAILED)
		return (erroring(0, ERROR_SEMAPHORE_CREATE), false);
	dining->writing = sem_open("second", O_CREAT, 0660, 1);
	if (dining->writing == SEM_FAILED)
		return (erroring(0, ERROR_SEMAPHORE_CREATE), false);
	return (true);
}
