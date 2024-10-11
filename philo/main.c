/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:27:55 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/11 18:02:43 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_input	input;
	t_philo	philo[MAX_PHILO];

	if (!parsing_check(ac, av))
		(printf("%s\n", USAGE), exit(1));
	memset(&input, 0, sizeof(input));
	memset(philo, 0, sizeof(philo));
}