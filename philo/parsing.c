/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:36:25 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/29 20:34:41 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long long	ft_isdigit(unsigned long long c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static unsigned long long	value_checker(char *str)
{
	unsigned long long	num;

	num = ft_atoi(str);
	if (num == 0)
		return (0);
	return (1);
}

static unsigned long long	check_if_only_digits(char *str)
{
	unsigned long long	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

static unsigned long long	check_minimum_time(char **av)
{
	if (ft_atoi(av[2]) < 60)
		return (0);
	if (ft_atoi(av[3]) < 60)
		return (0);
	if (ft_atoi(av[4]) < 60)
		return (0);
	return (1);
}

unsigned long long	parsing_check(unsigned long long ac, char **av)
{
	unsigned long long	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	if (ft_atoi(av[1]) > 200)
		return (0);
	if (!check_minimum_time(av))
		return (0);
	while (++i < ac)
	{
		if (!check_if_only_digits(av[i]))
			return (0);
		if (!value_checker(av[i]))
			return (0);
	}
	return (1);
}
