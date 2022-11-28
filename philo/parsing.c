/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:10:57 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:03:00 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	atoi_check(const char *str)
{
	int			i;
	int			t;
	long long	x;

	t = 1;
	i = 0;
	if (str[0] == 0)
		return (false);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
		if (str[i++] == '-')
			t = -1;
	x = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = (x * 10) + (str[i++] - '0');
		if ((x * t > 2147483647) || (x * t < -2147483648))
			return (false);
	}
	if (x * t <= 0)
		return (false);
	return (true);
}

static bool	check_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
		}
	}
	i = 0;
	while (++i < argc)
	{
		if (!atoi_check(argv[i]))
			return (false);
	}
	return (true);
}

bool	check_input(int argc, char **argv, char **envp)
{
	if (envp[0] == NULL)
		return (write(1, "no environment\n", \
			ft_strlen("no environment\n")), false);
	if (argc != 5 && argc != 6)
		return (write(1, "4 or 5 arguments needed\n", \
			ft_strlen("5 or 6 arguments needed\n")), false);
	if (!check_argv(argc, argv))
		return (write(1, "arguments incorrect\n", \
			ft_strlen("arguments incorrect\n")), false);
	return (true);
}
