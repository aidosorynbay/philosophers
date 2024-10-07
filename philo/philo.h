/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:14 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/07 14:23:57 by aorynbay         ###   ########.fr       */
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
	int				my_fork_locked;
	int				right_fork_locked;
	int				done_eating;
	int				eat_count;
	struct timeval	just_ate;
	struct s_philo	*next;
}	t_philo;

int		check_args(int ac, char **av);
int		late_eat(t_philo *philo, struct timeval *end);
int		ft_atoi(const char *str);
void	init_info(t_info *info, int ac, char **av);
void	init_philo(t_philo *philo[], t_info *info);
void	join_philo(t_philo *philo[], t_info *info);
void	*routine(void *structure);

void	taken_fork(t_philo *philo, struct timeval *start);
void	eating(t_philo *philo, struct timeval *start);
void	is_sleeping(t_philo *philo, struct timeval *start);
void	is_thinking(t_philo *philo, struct timeval *start);
void	is_dead(t_philo *philo, struct timeval *start);

void	c_sleep(int time_to);
void	take_forks(t_philo *philo, struct timeval *start);

#endif