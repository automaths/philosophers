/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_global.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:40 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:02:36 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!initing_mutex(dining))
		return (false);
	dining->count[NB_PHILO_MUTEXED] = 0;
	dining->count[NB_PHILO_THREADED] = 0;
	dining->el_muerte = 0;
	dining->el_full_bellies = 0;
	return (true);
}
