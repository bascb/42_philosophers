/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:24:04 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/27 18:45:00 by bcastelo         ###   ########.fr       */
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
