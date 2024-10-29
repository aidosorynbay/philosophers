/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:21:57 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/29 19:22:01 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	c_sleep(t_philo *philo, unsigned long long time_to)
{
	unsigned long long	start_time;

	start_time = get_time_ms(philo->input->start_time);
	while (!check_if_dead(philo) && get_time_ms(philo->input->start_time)
		- start_time < time_to)
		usleep(100);
}

void	eating(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[32m%llu %llu is eating\033[0m\n",
			get_time_ms(philo->input->start_time), philo->index + 1);
	safe_mutex_unlock(&philo->input->printf_mutex);
	c_sleep(philo, philo->input->time_to_eat);
}

void	sleeping(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[35m%llu %llu is sleeping\033[0m\n",
			get_time_ms(philo->input->start_time), philo->index + 1);
	safe_mutex_unlock(&philo->input->printf_mutex);
	c_sleep(philo, philo->input->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("%llu %llu is thinking\n",
			get_time_ms(philo->input->start_time), philo->index + 1);
	safe_mutex_unlock(&philo->input->printf_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->input->number_of_philosophers == 1)
		return (one_philo(philo), NULL);
	c_sleep(philo, philo->initial_wait);
	while (!check_if_dead(philo))
	{
		whole_process(philo);
		safe_mutex_lock(&philo->meals_eaten_mutex);
		if (philo->input->number_of_meals != 0
			&& philo->meals_eaten >= philo->input->number_of_meals)
		{
			safe_mutex_unlock(&philo->meals_eaten_mutex);
			safe_mutex_lock(&philo->input->all_meals_mutex);
			philo->input->all_meals++;
			safe_mutex_unlock(&philo->input->all_meals_mutex);
			return (NULL);
		}
		safe_mutex_unlock(&philo->meals_eaten_mutex);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
