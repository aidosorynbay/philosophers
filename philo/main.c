/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:27:55 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/29 20:32:59 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	printf("\033[34m%d %d has taken a fork\033[0m\n", 0, 1);
	usleep(philo->input->time_to_die * 1000);
	printf("\033[31m%llu %d died\033[0m\n", philo->input->time_to_die, 1);
}

int	main(int ac, char **av)
{
	t_input	input;
	t_philo	philo[MAX_PHILO];

	if (!parsing_check(ac, av))
		(printf("%s\n", USAGE), exit(1));
	memset(&input, 0, sizeof(input));
	memset(philo, 0, sizeof(philo));
	memset(&input.fork_state, 0, sizeof(input.fork_state));
	init_structs(philo, &input, av, ac);
	if (input.monitor)
		pthread_join(input.monitor, NULL);
	clear_philo_input(philo, &input);
}
