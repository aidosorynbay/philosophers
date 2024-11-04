/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:47:11 by aorynbay          #+#    #+#             */
/*   Updated: 2024/11/04 10:18:38 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 201
# elif MAX_PHILO > 201 || MAX_PHILO < 1
#  undef MAX_PHILO
#  define MAX_PHILO 201
# endif

# define USAGE "./philo num_philo die_time eat_time sleep_time [times_to_eat]\n"
# define AVAILABLE 0
# define LOCKED 1

typedef struct t_sinput
{
	unsigned long long				number_of_philosophers;
	unsigned long long				time_to_die;
	unsigned long long				time_to_eat;
	unsigned long long				time_to_sleep;
	unsigned long long				number_of_meals;
	unsigned long long				start_time;
	unsigned long long				all_meals;
	pthread_mutex_t					all_meals_mutex;
	pthread_t						philo[MAX_PHILO];
	pthread_mutex_t					forks[MAX_PHILO];
	unsigned long long				fork_state[MAX_PHILO];
	pthread_mutex_t					is_dead_mutex;
	pthread_mutex_t					printf_mutex;
	unsigned long long				is_dead;
	pthread_t						monitor;
}	t_input;

typedef struct t_sphilo
{
	unsigned long long				index;
	t_input							*input;
	unsigned long long				num_of_philo;
	unsigned long long				time_since_last_meal;
	pthread_mutex_t					t_since_last_meal_mutex;
	unsigned long long				meals_eaten;
	pthread_mutex_t					meals_eaten_mutex;
	pthread_mutex_t					meal_time_check_mutex;
	unsigned long long				initial_wait;
	pthread_mutex_t					*my_fork;
	pthread_mutex_t					*next_fork;
}	t_philo;

void				one_philo(t_philo *philo);

unsigned long long	parsing_check(unsigned long long ac, char **av);
unsigned long long	ft_atoi(const char *str);
void				safe_mutex_lock(pthread_mutex_t *mutex);
void				safe_mutex_unlock(pthread_mutex_t *mutex);
unsigned long long	get_time_ms(unsigned long long start_time);

void				init_structs(t_philo *philo, t_input *input,
						char **av, unsigned long long ac);

void				*monitor_r(void *arg);
unsigned long long	check_if_dead(t_philo *philo);

void				*routine(void *arg);
void				c_sleep(t_philo *philo, unsigned long long time_to);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				take_forks(t_philo *philo);
void				meal_count_add(t_philo *philo);
void				print_taken_fork(t_philo *philo);
void				meal_time_r(t_philo *philo);
void				release_forks(t_philo *philo);

void				clear_philo_input(t_philo *philo, t_input *input);
void				safe_join_thread(pthread_t thread);

void				even_philo(t_philo *philo);
void				whole_process(t_philo *philo);

#endif