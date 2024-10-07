/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:51:00 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/07 14:23:47 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	c_sleep(int time_to)
{
	struct timeval	now;
	struct timeval	changing;
	long			el;

	gettimeofday(&now, NULL);
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

void	take_forks(t_philo *philo, struct timeval *start)
{
	pthread_mutex_lock(&philo->my_fork);
	philo->my_fork_locked = 1;
	taken_fork(philo, start);
	pthread_mutex_lock(&philo->next->my_fork);
	philo->next->my_fork_locked = 1;
	taken_fork(philo, start);
}
