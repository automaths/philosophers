/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsartral <nsartral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:11:03 by nsartral          #+#    #+#             */
/*   Updated: 2022/11/28 14:03:08 by nsartral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			t;
	long long	x;

	t = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+' || str[i] == ' ')
		if (str[i++] == '-')
			t = -1;
	x = 0;
	while (str[i] >= '0' && str[i] <= '9')
		x = (x * 10) + (str[i++] - '0');
	x *= t;
	return (x);
}

void	ft_putnbr_positive(int n)
{
	char	c;

	if (n == 0)
	{
		write (1, "0", 1);
		return ;
	}
	if (n > 9)
		ft_putnbr_positive(n / 10);
	c = n % 10 + '0';
	write (1, &c, 1);
}
