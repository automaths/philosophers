/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:34 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:07:13 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	alone_dining(int die)
{
	int	ret;

	ret = now();
	write(1, "0 1 has taken a fork\n", ft_strlen("0 1 has taken a fork\n"));
	while (now() < ret + die)
		usleep(200);
	ft_putnbr_positive(die);
	write(1, " 1 died\n", ft_strlen(" 1 died\n"));
}

void	clear_table(t_global *dining)
{
	int	i;

	i = -1;
	while (++i < dining->infos[NB_PHILOSOPHERS])
		kill(dining->philosophers[i].pid, SIGKILL);
	sem_post(dining->writing);
	sem_close(dining->common_forks);
	sem_close(dining->writing);
	if (dining->philosophers)
		free(dining->philosophers);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	dining;

	if (!check_input(argc, argv, envp))
		return (0);
	if (ft_atoi(argv[1]) == 1)
	{
		alone_dining(ft_atoi(argv[2]));
		return (0);
	}
	if (!initing_global(&dining, argc, argv))
		return (0);
	if (!initing_philosophers(&dining))
		return (0);
	clear_table(&dining);
	return (0);
}
