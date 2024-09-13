/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:16:56 by aorynbay          #+#    #+#             */
/*   Updated: 2024/09/13 19:42:32 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *structure)
{
	t_philo	*philo;

	philo = (t_philo *)structure;
	printf("thread #: %d\n", philo->index);
	return (NULL);
}