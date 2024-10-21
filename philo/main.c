/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:27:55 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/17 17:46:46 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo()
{
	printf("\033[34m%d %d has taken a fork\033[0m\n", 0, 0);
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
	// safe_join_thread(input.monitor);
	pthread_join(input.monitor, NULL);
	clear_philo_input(philo, &input);
}