/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:32:40 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/28 08:19:47 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	run_simulation(params);
	clean_params(params);
	return (0);
}

void	create_philosophers(t_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < params->nbr_of_philos)
	{
		set_philo_data(params, i);
		pthread_create(&params->philosophers[i].id, NULL,
			manage_gathering, &params->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < params->nbr_of_philos)
		pthread_mutex_init(&params->forks[i++], NULL);
	pthread_mutex_lock(&params->mtx);
	params->sim_state = 1;
	params->limits->start_time = get_current_time();
	pthread_mutex_unlock(&params->mtx);
}

void	run_simulation(t_params *params)
{
	unsigned int	i;
	int				philo_died;

	philo_died = 0;
	while (!philo_died)
	{
		usleep(1000);
		i = -1;
		while (++i < params->nbr_of_philos)
		{
			if (!is_alive(params->philosophers[i].last_eat_start,
					params->limits->time_to_die))
			{
				print_log(&params->philosophers[i], "died");
				philo_died = 1;
				break ;
			}
		}
	}
	pthread_mutex_lock(&params->mtx);
	params->sim_state = 0;
	pthread_mutex_unlock(&params->mtx);
	i = -1;
	while (++i < params->nbr_of_philos)
		pthread_join(params->philosophers[i].id, params->philosophers[i].res);
}
