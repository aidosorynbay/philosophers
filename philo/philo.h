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

typedef struct t_sinput
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	pthread_t		philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	int				fork_state[MAX_PHILO];
	pthread_mutex_t	is_dead_mutex;
	int				is_dead;
	pthread_t		monitor;
} t_input;

typedef struct t_sphilo
{
	int				index;
	t_input			*input;
	int				time_since_last_meal;
	int				time_since_started;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*next_fork;
} t_philo;

int	parsing_check(int ac, char **av);
int	ft_atoi(const char *str);

#endif