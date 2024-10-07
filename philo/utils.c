/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:12:45 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/07 13:39:01 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		if (result >= LLONG_MAX && sign == -1)
			return (0);
		if (result >= LLONG_MAX)
			return (-1);
		str++;
	}
	return (result * sign);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

static int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i <= ac - 1)
	{
		if (!is_num(av[i++]))
			return (0);
	}
	return (1);
}

int	late_eat(t_philo *philo, struct timeval *end)
{
	long			seconds;
	long			useconds;
	long			elapsed;

	seconds = end->tv_sec - philo->just_ate.tv_sec;
	useconds = end->tv_usec - philo->just_ate.tv_usec;
	if (useconds < 0)
	{
		seconds -= 1;
		useconds += 1000000;
	}
	elapsed = (seconds * 1000) + (useconds / 1000);
	if (elapsed >= philo->philo_info->time_to_die)
		return (1);
	return (0);
}
