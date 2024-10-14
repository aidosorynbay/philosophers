/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:21:57 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:11 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	c_sleep(int time_to)
{
	struct timeval	now;
	struct timeval	changing;
	long			el;

	gettimeofday(&now, NULL);
	if (time_to == 0)
		return ;
	el = 0;
	while (1)
	{
		gettimeofday(&changing, NULL);
		el = ((changing.tv_sec - now.tv_sec) * 1000)
			+ ((changing.tv_usec - now.tv_usec) / 1000);
		if (el < time_to)
			usleep(100);
		else
			break ;
	}
}

static void	eating(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[32m%d %d is eating\033[0m\n", get_time_ms(philo->input->start_time), philo->index);	
	safe_mutex_unlock(&philo->input->printf_mutex);
	c_sleep(philo->input->time_to_eat); // implement
}

static void sleeping(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[35m%d %d is sleeping\033[0m\n", get_time_ms(philo->input->start_time), philo->index);	
	safe_mutex_unlock(&philo->input->printf_mutex);
	c_sleep(philo->input->time_to_eat); // implement
}

static void thinking(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("%d %d is thinking\n", get_time_ms(philo->input->start_time), philo->index);	
	safe_mutex_unlock(&philo->input->printf_mutex);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	if (philo->input->number_of_philosophers == 1)
		return (one_philo(), NULL); // implement
	c_sleep(philo->initial_wait);
	while (!check_if_dead(philo))
	{
		take_forks(philo);
		eating(philo);
		meal_time_r(philo);
		meal_count_add(philo);
		release_forks(philo);
		safe_mutex_lock(&philo->meals_eaten_mutex);
		if (philo->input->number_of_meals != 0 && philo->meals_eaten >= philo->input->number_of_meals)
			return (safe_mutex_unlock(&philo->meals_eaten_mutex), NULL);
		safe_mutex_unlock(&philo->meals_eaten_mutex);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
