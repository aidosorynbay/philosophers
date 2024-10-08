/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/08 14:58:49 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_process(t_philo *philo, struct timeval *start)
{
	pthread_mutex_lock(&philo->done_eating_mutex);
	if (philo->done_eating == 0)
	{
		pthread_mutex_unlock(&philo->done_eating_mutex);
		if (philo->index < philo->next->index)
			take_forks(philo, start);
		else
		{
			pthread_mutex_lock(&philo->next->my_fork);
			pthread_mutex_lock(&philo->next->my_fork_locked_mutex);
			philo->next->my_fork_locked = 1;
			pthread_mutex_unlock(&philo->next->my_fork_locked_mutex);
			taken_fork(philo, start);
			pthread_mutex_lock(&philo->my_fork);
			pthread_mutex_lock(&philo->my_fork_locked_mutex);
			philo->my_fork_locked = 1;
			pthread_mutex_unlock(&philo->my_fork_locked_mutex);
			taken_fork(philo, start);
		}
		eating(philo, start);
		gettimeofday(&philo->just_ate, NULL);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->my_fork);
		pthread_mutex_lock(&philo->my_fork_locked_mutex);
		philo->my_fork_locked = 0;
		pthread_mutex_unlock(&philo->my_fork_locked_mutex);
		pthread_mutex_unlock(&philo->next->my_fork);
		pthread_mutex_lock(&philo->next->my_fork_locked_mutex);
		philo->next->my_fork_locked = 0;
		pthread_mutex_unlock(&philo->next->my_fork_locked_mutex);
		pthread_mutex_lock(&philo->done_eating_mutex);
		philo->done_eating = 1;
	}
	pthread_mutex_unlock(&philo->done_eating_mutex);
}

static void	ft_logic(t_philo *philo, struct timeval *start)
{
	eating_process(philo, start);
	pthread_mutex_lock(&philo->done_eating_mutex);
	if (philo->done_eating == 1)
	{
		pthread_mutex_unlock(&philo->done_eating_mutex);
		is_sleeping(philo, start);
	}
	else
		pthread_mutex_unlock(&philo->done_eating_mutex);
	pthread_mutex_lock(&philo->done_eating_mutex);
	philo->done_eating = 0;
	pthread_mutex_unlock(&philo->done_eating_mutex);
	if (philo->my_fork_locked == 1 || philo->next->my_fork_locked == 1)
		is_thinking(philo, start);
}

void	*routine(void *structure)
{
	t_philo			*philo;

	philo = (t_philo *)structure;
	if (philo->philo_info->num_philo == 1)
		(is_dead(philo, &philo->philo_info->start_time), exit(EXIT_FAILURE));
	while (philo->is_philo_dead == 0)
	{
		if (philo->index % 2 != 0)
			ft_logic(philo, &philo->philo_info->start_time);
		else
		{
			usleep(100);
			ft_logic(philo, &philo->philo_info->start_time);
		}
		if (philo->eat_count == philo->philo_info->num_of_eats)
			break ;
		if (philo->is_philo_dead)
		{
			is_dead(philo, &philo->philo_info->start_time);
			break ;
		}
	}
	return (NULL);
}
