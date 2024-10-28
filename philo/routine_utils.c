/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:18:15 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/28 19:16:56 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_taken_fork(t_philo *philo)
{
	safe_mutex_lock(&philo->input->printf_mutex);
	if (!check_if_dead(philo))
		printf("\033[34m%d %d has taken a fork\033[0m\n", get_time_ms(philo->input->start_time), philo->index + 1);
	safe_mutex_unlock(&philo->input->printf_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		safe_mutex_lock(philo->my_fork);
		if (!philo->input->fork_state[philo->index])
			philo->input->fork_state[philo->index] = 1;
		print_taken_fork(philo);
		safe_mutex_lock(philo->next_fork);
		if (!philo->input->fork_state[(philo->index + 1) % philo->input->number_of_philosophers])
			philo->input->fork_state[(philo->index + 1) % philo->input->number_of_philosophers] = 1;
		print_taken_fork(philo);
	}
	else
	{
		safe_mutex_lock(philo->next_fork);
		if (!philo->input->fork_state[(philo->index + 1) % philo->input->number_of_philosophers])
			philo->input->fork_state[(philo->index + 1) % philo->input->number_of_philosophers] = 1;
		print_taken_fork(philo);
		safe_mutex_lock(philo->my_fork);
		if (!philo->input->fork_state[philo->index])
			philo->input->fork_state[philo->index] = 1;
		print_taken_fork(philo);
	}
}

void	meal_count_add(t_philo *philo)
{
	safe_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	safe_mutex_unlock(&philo->meals_eaten_mutex);
}

void	meal_time_r(t_philo *philo)
{
	safe_mutex_lock(&philo->t_since_last_meal_mutex);
	philo->time_since_last_meal = get_time_ms(0);
	safe_mutex_unlock(&philo->t_since_last_meal_mutex);
}

void	release_forks(t_philo *philo)
{
	philo->input->fork_state[philo->index] = 0;
	philo->input->fork_state[(philo->index + 1) % philo->input->number_of_philosophers] = 0;
	safe_mutex_unlock(philo->my_fork);
	safe_mutex_unlock(philo->next_fork);
	if (philo->index % 2 == 0 && philo->input->number_of_philosophers % 2)
		usleep(300);
}