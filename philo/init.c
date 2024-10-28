/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:20:58 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/28 19:58:37 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_thread(pthread_t *thread, const pthread_attr_t *attr, void *(*routine)(void *), void *arg)
{
	if (pthread_create(thread, attr, routine, arg) == 0)
		return ;
	perror("thread creation failed");
	exit(1);
}

static void	init_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) == 0)
		return ;
	perror("mutex init problem");
	exit(1);
}

static void	init_input(t_input *input, char **av, int ac)
{
	if (ac == 6)
		input->number_of_meals = ft_atoi(av[5]);
	else
		input->number_of_meals = 0;
	input->number_of_philosophers = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->is_dead = 0;
	input->start_time = 0;
	input->all_meals = 0;
	init_mutex(&input->all_meals_mutex);
	init_mutex(&input->is_dead_mutex);
	init_mutex(&input->printf_mutex);
	memset(input->fork_state, AVAILABLE, sizeof(input->fork_state));
}

static void	init_philo(t_philo *philo, t_input *input, int i)
{
	while (++i < input->number_of_philosophers)
	{
		philo[i].index = i;
		philo[i].input = input;
		philo[i].meals_eaten = 0;
		philo[i].my_fork = &input->forks[i];
		philo[i].next_fork = &input->forks[(i + 1) % input->number_of_philosophers];
		init_mutex(&philo[i].meals_eaten_mutex);
		init_mutex(&philo[i].meal_time_check_mutex);
		philo[i].time_since_last_meal = get_time_ms(0);
		init_mutex(&philo[i].t_since_last_meal_mutex);
		philo[i].initial_wait = (i % 2) * (input->time_to_eat / 2);
	}
}

void	init_structs(t_philo *philo, t_input *input, char **av, int ac)
{
	int	i;

	i = -1;
	init_input(input, av, ac);
	while (++i < input->number_of_philosophers)
		init_mutex(&input->forks[i]);
	i = -1;
	init_philo(philo, input, i);
	input->start_time = get_time_ms(0);
	create_thread(&input->monitor, NULL, &monitor_r, (void *)philo);
	i = -1;
	while (++i < input->number_of_philosophers)
		create_thread(&input->philo[i], NULL, &routine, (void *)&philo[i]);
}