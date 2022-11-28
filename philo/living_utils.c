/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   living_utils.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nsartral <nsartral@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/27 17:04:53 by nsartral		  #+#	#+#			 */
/*   Updated: 2022/11/27 17:07:15 by nsartral		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	write_state(t_struct *philosopher, time_t now, int type)
{
	pthread_mutex_lock(philosopher->writing);
	ft_putnbr_positive(now - philosopher->birth);
	write(1, " ", 1);
	ft_putnbr_positive(philosopher->number + 1);
	if (type == DISPLAY_FIRST_FORK || type == DISPLAY_SECOND_FORK)
		write(1, " has taken a fork\n", ft_strlen(" has taken a fork\n"));
	if (type == DISPLAY_EATING)
		write(1, " is eating\n", ft_strlen(" is eating\n"));
	if (type == DISPLAY_SLEEPING)
		write(1, " is sleeping\n", ft_strlen(" is sleeping\n"));
	if (type == DISPLAY_THINKING)
		write(1, " is thinking\n", ft_strlen(" is thinking\n"));
}

bool	writing(t_struct *philosopher, time_t now, int type)
{
	if (type == DISPLAY_DEATH)
	{
		pthread_mutex_lock(philosopher->writing);
		ft_putnbr_positive(now - philosopher->ate);
		write(1, " ", 1);
		ft_putnbr_positive(philosopher->number + 1);
		write(1, " died\n", ft_strlen(" died\n"));
		pthread_mutex_unlock(philosopher->writing);
		return (true);
	}
	if (type == MEALS_CHECK)
	{
		pthread_mutex_lock(philosopher->writing);
		write(1, "all philsophers have had their meals\n", \
			ft_strlen("all philsophers have had their meals\n"));
		pthread_mutex_unlock(philosopher->writing);
		return (true);
	}
	if (check_death(philosopher, type))
		return (true);
	if (check_meals(philosopher, type))
		return (true);
	write_state(philosopher, now, type);
	pthread_mutex_unlock(philosopher->writing);
	return (false);
}

bool	check_meals(t_struct *philosopher, int type)
{
	int	ret;

	ret = now();
	pthread_mutex_lock(philosopher->full_bellies);
	if (*philosopher->el_full_bellies == 1 || (philosopher->times_ate > \
		philosopher->infos[TARGET_MEALS] && \
		philosopher->infos[TARGET_MEALS] != -1))
	{
		if (*philosopher->el_full_bellies == 0)
		{
			*philosopher->el_full_bellies = 1;
			writing(philosopher, ret, MEALS_CHECK);
		}
		if (type == DISPLAY_FIRST_FORK)
			pthread_mutex_unlock(&philosopher->first_fork);
		if (type == DISPLAY_SECOND_FORK)
		{
			pthread_mutex_unlock(&philosopher->first_fork);
			pthread_mutex_unlock(philosopher->second_fork);
		}
		pthread_mutex_unlock(philosopher->full_bellies);
		return (true);
	}
	pthread_mutex_unlock(philosopher->full_bellies);
	return (false);
}

bool	check_death(t_struct *philosopher, int type)
{
	time_t	ret;

	pthread_mutex_lock(philosopher->muerte);
	ret = now();
	if (*philosopher->el_muerte == 1 || (ret - philosopher->ate > \
		philosopher->infos[TIME_TO_DIE]))
	{
		if (*philosopher->el_muerte == 0)
		{
			*philosopher->el_muerte = 1;
			writing(philosopher, ret, DISPLAY_DEATH);
		}
		if (type == DISPLAY_FIRST_FORK)
			pthread_mutex_unlock(&philosopher->first_fork);
		if (type == DISPLAY_SECOND_FORK || type == DISPLAY_EATING)
		{
			pthread_mutex_unlock(&philosopher->first_fork);
			pthread_mutex_unlock(philosopher->second_fork);
		}
		pthread_mutex_unlock(philosopher->muerte);
		return (true);
	}
	pthread_mutex_unlock(philosopher->muerte);
	return (false);
}
