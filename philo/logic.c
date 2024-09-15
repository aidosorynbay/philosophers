/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/15 16:27:07 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_process(t_philo *philo, struct timeval start)
{
	if (philo->done_eating == 0)
	{
		pthread_mutex_lock(&philo->my_fork);
		philo->my_fork_locked = 1;
		taken_fork(philo, &start);
		pthread_mutex_lock(&philo->next->my_fork);
		philo->next->my_fork_locked = 1;
		taken_fork(philo, &start);
		eating(philo, &start);
		pthread_mutex_unlock(&philo->my_fork);
		philo->my_fork_locked = 0;
		pthread_mutex_unlock(&philo->next->my_fork);
		philo->next->my_fork_locked = 0;
		philo->done_eating = 1;
	}
}

static void	ft_logic(t_philo *philo, struct timeval start)
{
	eating_process(philo, start);
	if (philo->done_eating == 1)
		is_sleeping(philo, &start);
	philo->done_eating = 0;
	if (philo->my_fork_locked == 1 || philo->next->my_fork_locked == 1)
		is_thinking(philo, &start);
}

void	*routine(void *structure)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *)structure;
	gettimeofday(&start, NULL);
	while (philo->is_philo_dead == 0)
	{
		if (philo->index % 2 != 0)
			ft_logic(philo, start);
		else
		{
			usleep(100);
			ft_logic(philo, start);
		}
	}
	return (NULL);
}
