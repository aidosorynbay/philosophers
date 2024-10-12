/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:45:38 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/12 20:50:09 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_join_thread(pthread_t thread, void **attr)
{
	if (pthread_join(thread, attr) == 0)
		return ;
	perror("join failed");
	exit(1);
}

void	clear_philo_input(t_philo *philo, t_input *input)
{
	int	i;

	i = 0;
	while (i++ < input->number_of_philosophers)
		safe_pthread_join(input->philo[i], NULL);
	i = 0;
	while (i++ < input->number_of_philosophers)
		safe_mutex_destroy(&input->forks[i]);
	safe_mutex_destroy(&input->is_dead_mutex);
	safe_mutex_destroy(&input->printf_mutex);
	i = 0;
	while (i++ < input->number_of_philosophers)
		(safe_mutex_destroy(&philo[i].meals_eaten_mutex)
			, safe_mutex_destroy(&philo[i].t_since_last_meal_mutex));
	exit(EXIT_SUCCESS);
}