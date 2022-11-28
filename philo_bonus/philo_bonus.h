/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:05:55 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/27 19:39:39 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h> 
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define NB_PHILOSOPHERS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define TARGET_MEALS 4
# define ERROR_SEMAPHORE_CREATE 1
# define ERROR_FORK_CREATE 2
# define ERROR_THREAD_CREATE 3
# define ERROR_TIME_DAY 4
# define IS_EATING 0
# define IS_SLEEPING 1
# define IS_THINKING 2
# define DISPLAY_FIRST_FORK 0 
# define DISPLAY_SECOND_FORK 1 
# define DISPLAY_EATING 2
# define DISPLAY_SLEEPING 3
# define DISPLAY_THINKING 4
# define DISPLAY_DEATH 5
# define TIMING 6
# define MEALS_CHECK 7

typedef struct s_struct
{
	int				number;
	int				infos[5];
	int				times_ate;
	int				pid;
	time_t			birth;
	time_t			synchronising;
	time_t			ate;
	sem_t			*common_forks;
	sem_t			*writing;
}					t_struct;

typedef struct s_global
{
	int				infos[5];
	t_struct		*philosophers;
	sem_t			*common_forks;
	sem_t			*writing;
}					t_global;

bool	check_input(int argc, char **argv, char **envp);
int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
bool	initing_philosophers(t_global *dining);
bool	initing_global(t_global *dining, int argc, char **argv);
void	erroring(int error, int type);
void	*living(t_struct *philosopher);
bool	initing_mutex(t_global *dining);
void	ft_putnbr_positive(int n);
long	now(void);
void	chronometer(time_t time, t_struct *philosopher, int type);
void	check_death(t_struct *philosopher, int type);
void	writing(t_struct *philosopher, time_t now, int type);
void	check_meals(t_struct *philosopher, int type);
void	write_state(t_struct *philosopher, time_t now, int type);
void	writing(t_struct *philosopher, time_t now, int type);
void	check_meals(t_struct *philosopher, int type);
void	check_death(t_struct *philosopher, int type);

#endif