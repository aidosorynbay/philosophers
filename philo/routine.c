/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:21:57 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/23 18:22:53 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	c_sleep(t_philo *philo, int time_to)
{
	int	start_time;

	start_time = get_time_ms(philo->input->start_time);
	while (!check_if_dead(philo) && get_time_ms(philo->input->start_time) - start_time < time_to)
		usleep(100);
}

static void	eating(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[32m%d %d is eating\033[0m\n", get_time_ms(philo->input->start_time), philo->index);	
	safe_mutex_unlock(&philo->input->printf_mutex);
	c_sleep(philo, philo->input->time_to_eat);
}

static void sleeping(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[35m%d %d is sleeping\033[0m\n", get_time_ms(philo->input->start_time), philo->index);	
	safe_mutex_unlock(&philo->input->printf_mutex);
	c_sleep(philo, philo->input->time_to_sleep);
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
		return (one_philo(), NULL);
	c_sleep(philo, philo->initial_wait);
	while (!check_if_dead(philo))
	{
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		meal_time_r(philo);
		meal_count_add(philo);
		safe_mutex_lock(&philo->meals_eaten_mutex);
		if (philo->input->number_of_meals != 0 && philo->meals_eaten >= philo->input->number_of_meals)
			return (safe_mutex_unlock(&philo->meals_eaten_mutex), NULL);
		safe_mutex_unlock(&philo->meals_eaten_mutex);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
