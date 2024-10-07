/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:13:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/15 16:13:56 by aorynbay         ###   ########.fr       */
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
	printf("\033[1;33m%ld %i has taken a fork\033[0m\n", elapsed, philo->index);
}

void	eating(t_philo *philo, struct timeval *start)
{
	struct timeval	current_time;
	long			elapsed;

	gettimeofday(&current_time, NULL);
	elapsed = ((current_time.tv_sec - start->tv_sec) * 1000)
		+ ((current_time.tv_usec - start->tv_usec) / 1000);
	if (elapsed >= philo->philo_info->time_to_die && philo->eat_count == 0)
	{
		is_dead(philo, start);
		exit(EXIT_FAILURE);
	}
	else if (philo->eat_count && late_eat(philo, &current_time))
	{
		is_dead(philo, start);
		exit(EXIT_FAILURE);
	}
	printf("\033[1;32m%ld %i is eating\033[0m\n", elapsed, philo->index);
	c_sleep(philo->philo_info->time_to_eat);
}

void	is_sleeping(t_philo *philo, struct timeval *start)
{
	struct timeval	current_time;
	long			elapsed;

	gettimeofday(&current_time, NULL);
	elapsed = ((current_time.tv_sec - start->tv_sec) * 1000)
		+ ((current_time.tv_usec - start->tv_usec) / 1000);
	printf("\033[1;34m%ld %i is sleeping\033[0m\n", elapsed, philo->index);
	c_sleep(philo->philo_info->time_to_sleep);
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
	printf("\033[1;35m%ld %i is thinking\033[0m\n", elapsed, philo->index);
}

void	is_dead(t_philo *philo, struct timeval *start)
{
	struct timeval	end;
	long			seconds;
	long			useconds;
	long			elapsed;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start->tv_sec;
	useconds = end.tv_usec - start->tv_usec;
	elapsed = (seconds * 1000) + (useconds / 1000);
	printf("\033[1;31m%ld %i died\033[0m\n", elapsed, philo->index);
}
