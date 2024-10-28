/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:56:49 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/28 20:41:41 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	int	condition;

	safe_mutex_lock(&philo->input->is_dead_mutex);
	condition = philo->input->is_dead;
	safe_mutex_unlock(&philo->input->is_dead_mutex);
	return (condition);
}

static int	meal_time_m(t_philo *philo)
{
	int	meal_time;

	safe_mutex_lock(&philo->meal_time_check_mutex);
	meal_time = get_time_ms(0) - philo->time_since_last_meal;
	safe_mutex_unlock(&philo->meal_time_check_mutex);
	return (meal_time);
}

static void	dying_sequence(t_philo *philo, int i)
{
	safe_mutex_lock(&philo[i].input->is_dead_mutex);
	philo[i].input->is_dead = 1;
	safe_mutex_unlock(&philo[i].input->is_dead_mutex);
	safe_mutex_lock(&philo[i].input->printf_mutex);
	printf("\033[31m%d %d died\033[0m\n",
		get_time_ms(philo[i].input->start_time), philo[i].index);
	safe_mutex_unlock(&philo[i].input->printf_mutex);
}

void	*monitor_r(void *arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->input->number_of_philosophers == 1)
		return (NULL);
	if (philo->input->number_of_meals == 0)
	{
		while (!check_if_dead(philo))
		{
			if (meal_time_m(&philo[i]) > philo[i].input->time_to_die)
			{
				dying_sequence(philo, i);
				break ;
			}
			i = (i + 1) % philo[i].input->number_of_philosophers;
		}
	}
	else
	{
		while (!check_if_dead(philo))
		{
			safe_mutex_lock(&philo->input->all_meals_mutex);
			if (philo->input->all_meals >= philo->input->number_of_philosophers)
			{
				safe_mutex_unlock(&philo->input->all_meals_mutex);
				return (NULL);
			}
			safe_mutex_unlock(&philo->input->all_meals_mutex);
			if (meal_time_m(&philo[i]) > philo[i].input->time_to_die
				&& (philo[i].meals_eaten < philo[i].input->number_of_meals))
			{
				dying_sequence(philo, i);
				break ;
			}
			i = (i + 1) % philo[i].input->number_of_philosophers;
		}
	}
	return (NULL);
}
