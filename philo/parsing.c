/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:36:25 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/10 17:56:55 by aorynbay         ###   ########.fr       */
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
		if (result >= INT_MAX && sign == -1)
			return (0);
		if (result >= INT_MAX)
			return (-1);
		str++;
	}
	return (result * sign);
}

static int	value_checker(char *str)
{
	int	num;
	num = ft_atoi(str);
	if (num == 0 || num < 0)
		return (0);
}

int	parsing_check(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 || ac != 6)
		return (0);
	while (i < ac)
	{
		if (!value_checker(av[i]))
			return (0);
		
	}
	
}