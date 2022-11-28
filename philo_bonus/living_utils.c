/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   living_utils.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nsartral <nsartral@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/11/27 16:55:53 by nsartral		  #+#	#+#			 */
/*   Updated: 2022/11/27 16:57:58 by nsartral		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_state(t_struct *philosopher, time_t now, int type)
{
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

void	writing(t_struct *philosopher, time_t now, int type)
{
	if (type == DISPLAY_DEATH)
	{
		sem_wait(philosopher->writing);
		ft_putnbr_positive(now - philosopher->birth);
		write(1, " ", 1);
		ft_putnbr_positive(philosopher->number + 1);
		write(1, " died\n", ft_strlen(" died\n"));
		sem_post(philosopher->writing);
		exit(0);
		return ;
	}
	if (type == MEALS_CHECK)
	{
		sem_wait(philosopher->writing);
		write(1, "all philosophers had their meals\n", \
			ft_strlen("all philosophers had their meals\n"));
		sem_post(philosopher->writing);
		return ;
	}
	check_death(philosopher, type);
	check_meals(philosopher, type);
	sem_wait(philosopher->writing);
	write_state(philosopher, now, type);
	sem_post(philosopher->writing);
}

void	check_meals(t_struct *philosopher, int type)
{
	if (philosopher->times_ate > philosopher->infos[TARGET_MEALS] && \
		philosopher->infos[TARGET_MEALS] != -1)
	{
		writing(philosopher, now(), MEALS_CHECK);
		if (type == DISPLAY_FIRST_FORK || type == DISPLAY_SECOND_FORK || \
			type == DISPLAY_EATING)
			sem_post(philosopher->common_forks);
		if (type == DISPLAY_SECOND_FORK || type == DISPLAY_EATING)
			sem_post(philosopher->common_forks);
		exit(0);
	}
}

void	check_death(t_struct *philosopher, int type)
{
	long	ret;

	ret = now();
	if (ret - philosopher->ate > philosopher->infos[TIME_TO_DIE])
	{
		if (type == DISPLAY_FIRST_FORK || type == DISPLAY_SECOND_FORK || \
			type == DISPLAY_EATING)
			sem_post(philosopher->common_forks);
		if (type == DISPLAY_SECOND_FORK || type == DISPLAY_EATING)
			sem_post(philosopher->common_forks);
		writing(philosopher, now(), DISPLAY_DEATH);
		exit(0);
	}
}
