/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:24:04 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/19 12:12:57 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	del_sem(sem_t *sem, char *name);

t_params	*clean_params(t_params *params)
{
	if (params->limits)
		free(params->limits);
	del_sem(params->forks, "/forks");
	del_sem(params->print, "/print");
	del_sem(params->init_time, "/time");
	del_sem(params->dead, "/dead");
	del_sem(params->meals_completed, "/meals");
	if (params->philosophers)
		free(params->philosophers);
	free(params);
	return (NULL);
}

void	del_sem(sem_t *sem, char *name)
{
	if (sem && sem != SEM_FAILED)
	{
		sem_close(sem);
		sem_unlink(name);
	}
}

void	print_log(t_philo *data, char *msg)
{
	unsigned long	now;

	now = get_current_time() - data->start_time;
	sem_wait(data->print);
	printf("%lu %u %s\n", now, data->philo_nbr, msg);
	sem_post(data->print);
}
