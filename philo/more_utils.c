/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:02:26 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/28 21:06:03 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_philo(t_philo *philo)
{
	safe_mutex_lock(philo->my_fork);
	if (!philo->input->fork_state[philo->index])
		philo->input->fork_state[philo->index] = 1;
	print_taken_fork(philo);
	safe_mutex_lock(philo->next_fork);
	if (!philo->input->fork_state[(philo->index + 1)
			% philo->input->number_of_philosophers])
	{
		philo->input->fork_state[(philo->index + 1)
			% philo->input->number_of_philosophers] = 1;
	}
}

void	whole_process(t_philo *philo)
{
	take_forks(philo);
	meal_time_r(philo);
	eating(philo);
	meal_count_add(philo);
	release_forks(philo);
}
