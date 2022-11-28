/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:36 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:02:29 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	erroring(int error, int type)
{
	if (type == ERROR_MUTEX_CREATE)
		printf("error, failed to create mutex: %s\n", strerror(error));
	if (type == ERROR_MUTEX_DESTROY)
		printf("error, failed to destroy mutex: %s\n", strerror(error));
	if (type == ERROR_THREAD_CREATE)
		printf("error, failed to create thread: %s\n", strerror(error));
	if (type == ERROR_TIME_DAY)
		printf("error, failed to get time of day: %s\n", strerror(errno));
}
