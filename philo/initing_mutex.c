/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initing_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:43 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:02:39 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	initing_mutex(t_global *dining)
{
	int	ret;

	ret = pthread_mutex_init(&dining->writing, NULL);
	if (ret != 0)
		return (erroring(ret, ERROR_MUTEX_CREATE), false);
	ret = pthread_mutex_init(&dining->muerte, NULL);
	if (ret != 0)
		return (erroring(ret, ERROR_MUTEX_CREATE), false);
	ret = pthread_mutex_init(&dining->full_bellies, NULL);
	if (ret != 0)
		return (erroring(ret, ERROR_MUTEX_CREATE), false);
	return (true);
}
