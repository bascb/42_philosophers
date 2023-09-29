/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:24:04 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/29 07:36:47 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_params	*clean_params(t_params *params)
{
	unsigned int	i;

	if (params->limits)
		free(params->limits);
	if (params->forks)
	{
		i = 0;
		while (i < params->nbr_of_philos)
			pthread_mutex_destroy(&params->forks[i++]);
		free(params->forks);
	}
	if (params->philosophers)
		free(params->philosophers);
	pthread_mutex_destroy(&params->mtx);
	free(params);
	return (NULL);
}

int	is_alive(unsigned long last_meal, unsigned long time_to_die)
{
	return (!check_timeout(last_meal, time_to_die));
}

int	get_sim_state(t_philo *data)
{
	int	state;

	pthread_mutex_lock(data->mtx);
	state = *data->sim_state;
	pthread_mutex_unlock(data->mtx);
	return (state);
}

void	set_sim_state(t_philo *data, int state)
{
	pthread_mutex_lock(data->mtx);
	*data->sim_state = state;
	pthread_mutex_unlock(data->mtx);
}
