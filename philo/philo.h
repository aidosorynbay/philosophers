/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:53:14 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/11 19:26:34 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # ifndef NUM_oF_THREAD NOT
// #  define NOT 10240
// # endif

typedef struct s_philo
{
	int				index;
	int				is_philo_dead;
	// pthread_mutex_t	
	// int	*left_fork = 0
	// int	*right_fork = 1 
	// forks
	// dead lock
	// meal lock
	// write lock
	// int	AOT = 7 // you shall decrement
}	t_philo;

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

int	check_args(int ac, char **av);
int	ft_atoi(const char *str);

#endif