/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/14 21:07:00 by aorynbay         ###   ########.fr       */
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
	struct timeval	end;
	long			seconds;
	long			useconds;
	long			elapsed;

	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start->tv_sec;
	useconds = end.tv_usec - start->tv_usec;

	elapsed = (seconds * 1000) + (useconds / 1000);
	printf("\033[1;32m%ld %i is eating\033[0m\n", elapsed, philo->index);
	usleep(philo->philo_info->time_to_eat * 1000);
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
	printf("\033[1;34m%ld %i is sleeping\033[0m\n", elapsed, philo->index);
	usleep(philo->philo_info->time_to_sleep * 1000);
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

void *routine(void *structure)
{
    t_philo *philo;
    struct timeval start;

    philo = (t_philo *)structure;
    gettimeofday(&start, NULL);

    while (philo->is_philo_dead == 0)
    {
        // Odd-numbered philosophers eat first
        if (philo->index % 2 != 0)
        {
            if (philo->done_eating == 0)
			{
				pthread_mutex_lock(&philo->my_fork);
				philo->my_fork_locked = 1;
				taken_fork(philo, &start);
				pthread_mutex_lock(&philo->next->my_fork);
				philo->next->my_fork_locked = 1;
				taken_fork(philo, &start);
				
				// Even-indexed philosopher is eating
				eating(philo, &start);
				
				// Release forks
				pthread_mutex_unlock(&philo->my_fork);
				philo->my_fork_locked = 0;
				pthread_mutex_unlock(&philo->next->my_fork);
				philo->next->my_fork_locked = 0;
				philo->done_eating = 1;
			}
            
            // Sleep and think after eating
			if (philo->done_eating == 1)
			{
            	is_sleeping(philo, &start);
			}
			philo->done_eating = 0;
            if (philo->my_fork_locked == 1 || philo->next->my_fork_locked == 1)
            {
                is_thinking(philo, &start);
                // usleep(100); // Short delay to avoid CPU overload
            }
        }
        else
        {
            // Sleep a bit to ensure odd philosophers go first
            usleep(100);  // Adjust timing if needed
            
            // Even-numbered philosophers eat after odd-numbered ones
            if (philo->done_eating == 0)
			{
				pthread_mutex_lock(&philo->my_fork);
				philo->my_fork_locked = 1;
				taken_fork(philo, &start);
				pthread_mutex_lock(&philo->next->my_fork);
				philo->next->my_fork_locked = 1;
				taken_fork(philo, &start);
				
				// Even-indexed philosopher is eating
				eating(philo, &start);
				
				// Release forks
				pthread_mutex_unlock(&philo->my_fork);
				philo->my_fork_locked = 0;
				pthread_mutex_unlock(&philo->next->my_fork);
				philo->next->my_fork_locked = 0;
				philo->done_eating = 1;
			}
            // Sleep and think after eating
			if (philo->done_eating == 1)
			{
            	is_sleeping(philo, &start);
			}
			philo->done_eating = 0;
			if (philo->my_fork_locked == 1 || philo->next->my_fork_locked == 1)
            {
                is_thinking(philo, &start);
                // usleep(100); // Short delay to avoid CPU overload
            }
        }
        // Short delay to avoid high CPU usage
        // usleep(100);
    }
    return NULL;
}





