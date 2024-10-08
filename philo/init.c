/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:44:08 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/08 17:01:56 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_info(t_info *info, int ac, char **av)
{
	if (ac == 6)
		info->num_of_eats = ft_atoi(av[5]);
	info->num_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
}

static void	link_philos(t_philo *philo[], t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (i < info->num_philo - 1)
			philo[i]->next = philo[i + 1];
		else
			philo[i]->next = philo[0];
		i++;
	}
}

static void	link_forks(t_philo *philo[], t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (i < info->num_philo - 1)
		{
			philo[i]->next->my_fork = philo[i + 1]->my_fork;
			philo[i]->next->my_fork_locked = philo[i + 1]->my_fork_locked;
		}
		else
		{
			philo[i]->next->my_fork = philo[0]->my_fork;
			philo[i]->next->my_fork_locked = philo[0]->my_fork_locked;
		}
		i++;
	}
}

static void	create_thread(t_philo *philo[], t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_create(&philo[i]->thread, NULL, routine, (void *)philo[i]))
			(perror("Failed creating thread."), exit(1));
		i++;
	}
}

void	init_philo(t_philo *philo[], t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			(perror("Malloc error."), exit(1));
		philo[i]->index = i;
		philo[i]->philo_info = info;
		pthread_mutex_init(&philo[i]->is_dead_mutex, NULL);
		philo[i]->my_fork_locked = 0;
		pthread_mutex_init(&philo[i]->my_fork_locked_mutex, NULL);
		philo[i]->done_eating = 0;
		pthread_mutex_init(&philo[i]->done_eating_mutex, NULL);
		philo[i]->eat_count = 0;
		pthread_mutex_init(&philo[i]->eat_count_mutex, NULL);
		pthread_mutex_init(&philo[i]->my_fork, NULL);
		i++;
	}
	link_philos(philo, info);
	link_forks(philo, info);
	gettimeofday(&info->start_time, NULL);
	create_thread(philo, info);
	join_philo(philo, info);
}
