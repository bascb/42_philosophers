/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:59 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/05 14:54:22 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*manage_gathering(void *arg)
{
	t_philo	*data;

	data = (t_philo *) arg;
	printf("I am philo number: %u\n", data->philo_nbr);
	return ((void *)(long)data->philo_nbr);
}
