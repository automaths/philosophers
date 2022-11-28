/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:59:44 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/27 19:37:20 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h> 

# define NB_PHILOSOPHERS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define TARGET_MEALS 4
# define ERROR_MUTEX_CREATE 1
# define ERROR_MUTEX_DESTROY 2
# define ERROR_THREAD_CREATE 3
# define ERROR_TIME_DAY 4
# define NB_PHILO_MUTEXED 0
# define NB_PHILO_THREADED 1
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
	int					number;
	int					infos[5];
	int					times_ate;
	int					*el_muerte;
	int					*el_full_bellies;
	time_t				birth;
	time_t				synchronising;
	time_t				ate;
	pthread_t			living;
	pthread_mutex_t		first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*writing;
	pthread_mutex_t		*muerte;
	pthread_mutex_t		*full_bellies;
}						t_struct;

typedef struct s_global
{
	int					infos[5];
	t_struct			*philosophers;
	pthread_mutex_t		writing;
	pthread_mutex_t		muerte;
	pthread_mutex_t		full_bellies;
	int					count[2];
	int					el_muerte;
	int					el_full_bellies;
}						t_global;

bool	check_input(int argc, char **argv, char **envp);
int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
bool	initing_philosophers(t_global *dining);
bool	initing_global(t_global *dining, int argc, char **argv);
void	erroring(int error, int type);
void	*living(void *arg);
bool	initing_mutex(t_global *dining);
void	ft_putnbr_positive(int n);
long	now(void);
bool	chronometer(time_t time, t_struct *philosopher, int type);
bool	check_death(t_struct *philosopher, int type);
bool	writing(t_struct *philosopher, time_t now, int type);
bool	check_meals(t_struct *philosopher, int type);
bool	check_death(t_struct *philosopher, int type);
bool	check_meals(t_struct *philosopher, int type);
bool	writing(t_struct *philosopher, time_t now, int type);

#endif