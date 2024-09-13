/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:14 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/13 19:42:26 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_THREADS 200

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_info
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eats;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	int				is_philo_dead;
	t_info			*philo_info;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	right_fork;
	struct s_philo	*next;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	meallock;
	pthread_mutex_t	writelock;
}	t_philo;

int		check_args(int ac, char **av);
int		ft_atoi(const char *str);
void	init_info(t_info *info, int ac, char **av);
void	init_philo(t_philo *philo[], t_info *info);
void	join_philo(t_philo *philo[], t_info *info);
void	*routine(void *structure);

#endif