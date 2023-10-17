/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:59 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/17 13:53:47 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				get_sim_state(t_philo *data);

void			set_sim_state(t_philo *data, int state);

unsigned long	get_sim_start(t_philo *data);

void			go_eat(t_philo *data);

void			go_sleep(t_philo *data);

void			go_think(t_philo *data);

void	*manage_gathering(void *arg)
{
	t_philo			*data;

	data = (t_philo *) arg;
	if (data->philo_nbr % 2 == 0)
		data->state = SLEEPING;
	while (!get_sim_start(data))
		usleep(1);
	pthread_mutex_lock(data->mtx);
	data->last_eat_start = data->limits->start_time;
	data->start_time = data->limits->start_time;
	pthread_mutex_unlock(data->mtx);
	while (get_sim_state(data))
	{
		if (data->state == THINKING && get_sim_state(data))
			go_think(data);
		if (data->state == EATING && get_sim_state(data))
			go_eat(data);
		if (data->state == SLEEPING && get_sim_state(data))
			go_sleep(data);
	}
	return ((void *)(long)data->philo_nbr);
}

void	go_eat(t_philo *data)
{
	if (data->nbr_of_philos > 1)
	{
		sem_wait(data->forks);
		print_log(data, "has taken a fork");
		sem_wait(data->forks);
		print_log(data, "has taken a fork");
		data->last_eat_start = get_current_time();
		data->meals_nbr++;
		print_log(data, "is eating");
		usleep(data->time_to_eat * 1000);
		sem_post(data->forks);
		sem_post(data->forks);
	}
	data->state = SLEEPING;
}

void	go_sleep(t_philo *data)
{
	print_log(data, "is sleeping");
	data->last_sleep_start = get_current_time();
	usleep(data->time_to_sleep * 1000);
	data->state = THINKING;
}

void	go_think(t_philo *data)
{
	print_log(data, "is thinking");
	data->state = EATING;
}

void	print_log(t_philo *data, char *msg)
{
	unsigned long	now;

	now = get_current_time() - data->start_time;
	sem_wait(data->print);
	if (*data->sim_state)
		printf("%lu %u %s\n", now, data->philo_nbr, msg);
	sem_post(data->print);
