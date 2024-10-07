/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:13:45 by aorynbay          #+#    #+#             */
/*   Updated: 2024/10/07 15:22:01 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo[MAX_THREADS];
	t_info	*info;

	if (!check_args(ac, av)) // add > 0?
		return (printf("invalid args."), 0);
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	init_info(info, ac, av);
	init_philo(philo, info);
	// free_mem();
}
