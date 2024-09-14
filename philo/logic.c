/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/14 15:59:14 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taken_fork(t_philo *philo, struct timeval *start)
{
	struct timeval	end;
	long			seconds;
	long			useconds;
	long			elapsed;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start->tv_sec;
	useconds = end.tv_usec - start->tv_usec;

	elapsed = (seconds * 1000) + (useconds / 1000);
	printf("%ld %i has taken a fork\n", elapsed, philo->index);
}

void	eating(t_philo *philo, struct timeval *start)
{
	struct timeval	end;
	long			seconds;
	long			useconds;
	long			elapsed;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start->tv_sec;
	useconds = end.tv_usec - start->tv_usec;

	elapsed = (seconds * 1000) + (useconds / 1000);
	printf("%ld %i is eating\n", elapsed, philo->index);
}

void	is_sleeping(t_philo *philo, struct timeval *start)
{
	struct timeval	end;
	long			seconds;
	long			useconds;
	long			elapsed;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start->tv_sec;
	useconds = end.tv_usec - start->tv_usec;

	elapsed = (seconds * 1000) + (useconds / 1000);
	printf("%ld %i is sleeping\n", elapsed, philo->index);
}

void	is_thinking(t_philo *philo, struct timeval *start)
{
	struct timeval	end;
	long			seconds;
	long			useconds;
	long			elapsed;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start->tv_sec;
	useconds = end.tv_usec - start->tv_usec;

	elapsed = (seconds * 1000) + (useconds / 1000);
	printf("%ld %i is thinking\n", elapsed, philo->index);
}	

void	*routine(void *structure)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *)structure;
	gettimeofday(&start, NULL);
	while (philo->is_philo_dead == 0)
	{
		if (philo->my_fork_locked == 0 && philo->right_fork_locked == 0)
		{
			pthread_mutex_lock(&philo->my_fork);
			taken_fork(philo, &start);
			philo->my_fork_locked = 1;
			pthread_mutex_lock(&philo->right_fork);
			taken_fork(philo, &start);
			eating(philo, &start);
			philo->right_fork_locked = 1;
			usleep(philo->philo_info->time_to_eat);
			pthread_mutex_unlock(&philo->my_fork);
			philo->my_fork_locked = 0;
			pthread_mutex_unlock(&philo->right_fork);
			philo->right_fork_locked = 0;
		}
		is_sleeping(philo, &start);
		usleep(philo->philo_info->time_to_sleep);
		is_thinking(philo, &start);
	}
	return (NULL);
}
