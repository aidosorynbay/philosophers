/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:27:55 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/12 20:48:40 by aorynbay         ###   ########.fr       */
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
	memset(&input.fork_state, 0, sizeof(input.fork_state));
	init_structs(philo, &input, av, ac);
	safe_join_thread(input.monitor, NULL);
	clear_philo_input(philo, &input);
}