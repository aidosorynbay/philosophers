/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/07 14:21:37 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_process(t_philo *philo, struct timeval *start)
{
	if (philo->done_eating == 0)
	{
		if (philo->index < philo->next->index)
			take_forks(philo, start);
		else
		{
			pthread_mutex_lock(&philo->next->my_fork);
			philo->next->my_fork_locked = 1;
			taken_fork(philo, start);
			pthread_mutex_lock(&philo->my_fork);
			philo->my_fork_locked = 1;
			taken_fork(philo, start);
		}
		taken_fork(philo, start);
		eating(philo, start);
		gettimeofday(&philo->just_ate, NULL);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->my_fork);
		philo->my_fork_locked = 0;
		pthread_mutex_unlock(&philo->next->my_fork);
		philo->next->my_fork_locked = 0;
		philo->done_eating = 1;
	}
}

static void	ft_logic(t_philo *philo, struct timeval *start)
{
	eating_process(philo, start);
	if (philo->done_eating == 1)
		is_sleeping(philo, start);
	philo->done_eating = 0;
	if (philo->my_fork_locked == 1 || philo->next->my_fork_locked == 1)
		is_thinking(philo, start);
}

void	*routine(void *structure)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *)structure;
	gettimeofday(&start, NULL);
	if (philo->philo_info->num_philo == 1)
		(is_dead(philo, &start), exit(EXIT_FAILURE));
	while (philo->is_philo_dead == 0)
	{
		if (philo->index % 2 != 0)
			ft_logic(philo, &start);
		else
		{
			usleep(100);
			ft_logic(philo, &start);
		}
		if (philo->eat_count == philo->philo_info->num_of_eats)
			break ;
		if (philo->is_philo_dead)
		{
			is_dead(philo, &start);
			break ;
		}
	}
	return (NULL);
}
