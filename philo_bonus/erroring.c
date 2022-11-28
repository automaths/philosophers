/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:10 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:06:57 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	erroring(int error, int type)
{
	if (type == ERROR_SEMAPHORE_CREATE)
		printf("error, failed to create semaphore: %s\n", strerror(errno));
	if (type == ERROR_FORK_CREATE)
		printf("error, failed to destroy fork: %s\n", strerror(errno));
	if (type == ERROR_THREAD_CREATE)
		printf("error, failed to create thread: %s\n", strerror(error));
	if (type == ERROR_TIME_DAY)
		printf("error, failed to get time of day: %s\n", strerror(errno));
}
