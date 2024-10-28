/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:36:25 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/28 20:42:16 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	value_checker(char *str)
{
	int	num;

	num = ft_atoi(str);
	if (num == 0 || num < 0)
		return (0);
	return (1);
}

static int	check_if_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

static int	check_minimum_time(char **av)
{
	if (ft_atoi(av[2]) < 60)
		return (0);
	if (ft_atoi(av[3]) < 60)
		return (0);
	if (ft_atoi(av[4]) < 60)
		return (0);
	return (1);
}

int	parsing_check(int ac, char **av)
{
	int	i;

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
