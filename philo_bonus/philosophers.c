/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:32:40 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/01 11:51:21 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	stop_simulation(t_params *params);

int	main(int argc, char **argv)
{
	t_params		*params;

	if (argc != 5 && argc != 6)
	{
		print_help(argv);
		return (0);
	}
	params = get_params(argc, argv);
	if (params == NULL)
		return (1);
	create_philosophers(params);
	control_simulation(params);
	clean_params(params);
	return (0);
}

void	create_philosophers(t_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < params->nbr_of_philos)
		pthread_mutex_init(&params->forks[i++], NULL);
	i = 0;
	while (i < params->nbr_of_philos)
		set_philo_data(params, i++);
	i = 0;
	while (i < params->nbr_of_philos)
	{
		pthread_create(&params->philosophers[i].id, NULL,
			manage_gathering, &params->philosophers[i]);
		i++;
	}
	pthread_mutex_lock(&params->mtx);
	params->sim_state = 1;
	params->limits->start_time = get_current_time();
	pthread_mutex_unlock(&params->mtx);
}

void	control_simulation(t_params *params)
{
	unsigned int	i;
	int				stop_sim;

	stop_sim = 0;
	while (!stop_sim)
	{
		usleep(1000);
		stop_sim = stop_simulation(params);
	}
	pthread_mutex_lock(&params->mtx);
	params->sim_state = 0;
	pthread_mutex_unlock(&params->mtx);
	i = -1;
	while (++i < params->nbr_of_philos)
		pthread_join(params->philosophers[i].id, params->philosophers[i].res);
}

int	stop_simulation(t_params *params)
{
	unsigned int	i;
	unsigned int	meals_completed;
	unsigned int	meals_nbr;
	unsigned long	last_eat;

	meals_completed = 0;
	if (params->meals_nbr)
		meals_completed = 1;
	i = -1;
	while (++i < params->nbr_of_philos)
	{
		pthread_mutex_lock(&params->mtx);
		last_eat = params->philosophers[i].last_eat_start;
		meals_nbr = params->philosophers[i].meals_nbr;
		pthread_mutex_unlock(&params->mtx);
		if (!is_alive(last_eat, params->limits->time_to_die))
		{
			print_log(&params->philosophers[i], "died");
			return (1);
		}
		if (params->meals_nbr && meals_nbr < params->meals_nbr)
			meals_completed = 0;
	}
	return (meals_completed);
}
