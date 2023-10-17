/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:59 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/17 22:57:00 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	go_eat(t_philo *data);

void	go_sleep(t_philo *data);

void	go_think(t_philo *data);

void	*check_dead(void *arg);

void	*manage_gathering(void *arg)
{
	t_philo		*data;
	pthread_t	tid;

	data = (t_philo *) arg;
	if (data->philo_nbr % 2 == 0)
		data->state = SLEEPING;
	sem_wait(data->init_time);
	data->start_time = get_current_time();
	data->last_eat_start = data->start_time;
	sem_post(data->init_time);
	pthread_create(&tid, NULL, check_dead, data);
	while (1)
	{
		if (data->state == THINKING)
			go_think(data);
		if (data->state == EATING)
			go_eat(data);
		if (data->state == SLEEPING)
			go_sleep(data);
	}
	exit(0);
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

void	*check_dead(void *arg)
{
	t_philo			*data;

	data = (t_philo *) arg;
	while (1)
	{
		usleep(1000);
		if (check_timeout(data->last_eat_start, data->time_to_die))
		{
			print_log(data, "died");
			sem_post(data->dead);
			exit(0);
		}
	}
}
