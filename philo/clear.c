/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:45:38 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/28 20:37:44 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) == 0)
		return ;
	perror("failed to destroy mutex");
	exit(1);
}

void	safe_join_thread(pthread_t thread)
{
	if (pthread_join(thread, NULL) == 0)
		return ;
	perror("join failed");
	exit(1);
}

void	clear_philo_input(t_philo *philo, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->number_of_philosophers)
	{
		pthread_join(input->philo[i], NULL);
	}
	i = -1;
	while (++i < input->number_of_philosophers)
		safe_mutex_destroy(&input->forks[i]);
	pthread_mutex_destroy(&input->is_dead_mutex);
	pthread_mutex_destroy(&input->printf_mutex);
	i = -1;
	while (i++ < input->number_of_philosophers)
		(pthread_mutex_destroy(&philo[i].meals_eaten_mutex)
			, pthread_mutex_destroy(&philo[i].t_since_last_meal_mutex));
	exit(EXIT_SUCCESS);
}
