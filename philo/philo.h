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
#  define MAX_PHILO 200
# elif MAX_PHILO > 200 || MAX_PHILO < 1
#  undef MAX_PHILO
#  define MAX_PHILO 200
# endif

# define USAGE "./philo num_philo die_time eat_time sleep_time [times_to_eat]\n"
# define AVAILABLE 0
# define LOCKED 1

typedef struct t_sinput
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				start_time;
	int				all_meals;
	pthread_mutex_t	all_meals_mutex;
	pthread_t		philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	int				fork_state[MAX_PHILO];
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	printf_mutex;
	int				is_dead;
	pthread_t		monitor;
} t_input;

typedef struct t_sphilo
{
	int				index;
	t_input			*input;
	int				time_since_last_meal;
	pthread_mutex_t	t_since_last_meal_mutex;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
	int				initial_wait;
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*next_fork;
} t_philo;

void	one_philo(t_philo *philo);

int		parsing_check(int ac, char **av);
int		ft_atoi(const char *str);
void	safe_mutex_lock(pthread_mutex_t *mutex);
void	safe_mutex_unlock(pthread_mutex_t *mutex);
int		get_time_ms(int start_time);

void	init_structs(t_philo *philo, t_input *input, char **av, int ac);

void	*monitor_r(void *arg);
int		check_if_dead(t_philo *philo);

void	*routine(void *arg);
void	c_sleep(t_philo *philo, int time_to);
void	take_forks(t_philo *philo);
void	meal_count_add(t_philo *philo);
void	meal_time_r(t_philo *philo);
void	release_forks(t_philo *philo);

void	safe_join_thread(pthread_t thread);
void	clear_philo_input(t_philo *philo, t_input *input);

#endif