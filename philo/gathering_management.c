/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:59 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/06 14:09:41 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*manage_gathering(void *arg)
{
	t_philo			*data;
	unsigned long	now;
	unsigned long	start;
	unsigned long	sleep_time;

	data = (t_philo *) arg;
	now = 0;
	sleep_time = 10 * data->philo_nbr;
	while (!data->limits->start_time)
		usleep(1);
	start = get_current_time();
	now = start;
	while (*data->sim_state && now < start + sleep_time)
	{
		usleep(1);
		now = get_current_time();
	}
	if (*data->sim_state)
	{
		*data->sim_state = 0;
		printf("%lu %u is here\n", now - data->limits->start_time, data->philo_nbr);
	}
	return ((void *)(long)data->philo_nbr);
}
