/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/13 21:15:33 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *structure)
{
	t_philo	*philo;

	philo = (t_philo *)structure;
	// printf("thread #: %d\n", philo->index);
	while (philo->is_philo_dead == 0)
	{
		if (philo->my_fork_locked == 0 && philo->right_fork_locked == 0)
		{
			pthread_mutex_lock(&philo->my_fork);
			philo->my_fork_locked = 1;
			pthread_mutex_lock(&philo->right_fork);
			philo->right_fork_locked = 1;
			printf("Philo %d is eating.\n", philo->index);
			usleep(philo->philo_info->time_to_eat);
			pthread_mutex_unlock(&philo->my_fork);
			philo->my_fork_locked = 0;
			pthread_mutex_unlock(&philo->right_fork);
			philo->right_fork_locked = 0;
		}
		printf("Philo %d is sleeping.\n", philo->index);
		usleep(philo->philo_info->time_to_sleep);
	}
	return (NULL);
}
