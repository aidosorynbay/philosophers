/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:13:45 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/12 09:40:47 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *structure)
{
	t_philo *philo;

	philo = (t_philo *)structure;

	printf("th #: %d\n", philo->index);
	return (NULL);
}

int	main(int ac, char **av)
{
	int			i;
	int			num_threads;
	t_philo		*philo_info;
	pthread_t	*th;

	if (!check_args(ac, av))
		return (0);
	i = 0;
	num_threads = ft_atoi(av[1]);
	th = malloc(num_threads * sizeof(pthread_t));
	philo_info = malloc(num_threads * sizeof(t_philo));
	// add malloc check
	// if (pthread_create(&th[i], NULL, &monitoring_routine, (void *)&philo_info[i]))
		// return (perror("uncle"), 404);
	while (i < num_threads)
	{
		philo_info[i].index = malloc(sizeof(int));
		(philo_info[i].index) = i;
		if (pthread_create(&th[i], NULL, &routine, (void *)&philo_info[i]))
			return (perror("Thread creation failed"), 1);
		i++;
	}
	while (--num_threads)
	{
		if (pthread_join(th[num_threads], NULL))
			return (perror("join failed bruh"), 2);
	}
	// add frees
	return (0);
}
