/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:59 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/28 08:07:01 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		get_sim_state(t_philo *data);

void	set_sim_state(t_philo *data, int state);

void	*manage_gathering(void *arg)
{
	t_philo			*data;

	data = (t_philo *) arg;
	if (data->philo_nbr % 2 == 0)
		data->state = THINKING;
	while (!data->limits->start_time)
		usleep(1);
	pthread_mutex_lock(data->mtx);
	data->last_eat_start = data->limits->start_time;
	pthread_mutex_unlock(data->mtx);
	while (get_sim_state(data))
	{
		if (data->state == THINKING)
		{
			print_log(data, "is thinking");
			usleep((5) * 1000);
			data->state = EATING;
		}
		if (data->state == EATING)
		{
			if (data->nbr_of_philos > 1)
			{
				pthread_mutex_lock(data->left);
				print_log(data, "has taken a fork");
				pthread_mutex_lock(data->right);
				print_log(data, "has taken a fork");
				print_log(data, "is eating");
				pthread_mutex_lock(data->mtx);
				data->last_eat_start = get_current_time();
				data->meals_nbr++;
				pthread_mutex_unlock(data->mtx);
				usleep(data->limits->time_to_eat * 1000);
				pthread_mutex_unlock(data->right);
				pthread_mutex_unlock(data->left);
			}
			data->state = SLEEPING;
		}
		if (data->state == SLEEPING)
		{
			print_log(data, "is sleeping");
			data->last_sleep_start = get_current_time();
			usleep(data->limits->time_to_sleep * 1000);
			data->state = THINKING;
		}
	}
	return ((void *)(long)data->philo_nbr);
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

void	print_log(t_philo *data, char *msg)
{
	unsigned long	now;

	now = get_current_time() - data->limits->start_time;
	pthread_mutex_lock(data->mtx);
	if (*data->sim_state)
		printf("%lu %u %s\n", now, data->philo_nbr, msg);
	pthread_mutex_unlock(data->mtx);
}
