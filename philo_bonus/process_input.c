/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:51:38 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/18 19:59:14 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_digits(char *str);

int	check_params(int argc, char **argv);

int	get_nbr_of_philos(t_params *params, char *str)
{
	params->nbr_of_philos = ft_atou(str);
	if (!params->nbr_of_philos)
		return (0);
	if (params->nbr_of_philos > 200)
	{
		printf("Number of philosophers (%d) exceeds the limit of 200\n",
			params->nbr_of_philos);
		return (0);
	}
	return (1);
}

int	get_limits(t_params *params, char **argv)
{
	params->limits = ft_calloc(1, sizeof(t_limits));
	if (!params->limits)
	{
		printf("Unable to alloc memory for limits structure\n");
		clean_params(params);
		return (0);
	}
	params->limits->time_to_die = ft_atoul(argv[2]);
	params->limits->time_to_eat = ft_atoul(argv[3]);
	params->limits->time_to_sleep = ft_atoul(argv[4]);
	return (1);
}

int	create_philo_fork_arrays(t_params *params)
{
	params->philosophers = ft_calloc(params->nbr_of_philos, sizeof(t_philo));
	if (!params->philosophers)
	{
		printf("Unable to alloc memory for philosophers\n");
		clean_params(params);
		return (0);
	}
	params->forks = sem_open("/forks", O_CREAT, 0, params->nbr_of_philos);
	if (params->forks == SEM_FAILED)
	{
		printf("Unable to create semaphore for forks\n");
		clean_params(params);
		return (0);
	}
	return (1);
}

t_params	*get_params(int argc, char **argv)
{
	t_params	*params;

	if (check_params(argc, argv) == -1)
		return (NULL);
	params = ft_calloc(1, sizeof(t_params));
	if (params == NULL)
		return (NULL);
	if (!get_nbr_of_philos(params, argv[1]))
		return (clean_params(params));
	if (!get_limits(params, argv))
		return (clean_params(params));
	if (argc == 6)
		params->meals_nbr = ft_atou(argv[5]);
	if (!create_philo_fork_arrays(params))
		return (clean_params(params));
	if (!create_semaphores(params))
		return (NULL);
	return (params);
}

void	set_philo_data(t_params *params, int i)
{
	params->philosophers[i].philo_nbr = i + 1;
	params->philosophers[i].nbr_of_philos = params->nbr_of_philos;
	params->philosophers[i].sim_state = &params->sim_state;
	params->philosophers[i].limits = params->limits;
	params->philosophers[i].time_to_die = params->limits->time_to_die;
	params->philosophers[i].time_to_eat = params->limits->time_to_eat;
	params->philosophers[i].time_to_sleep = params->limits->time_to_sleep;
	params->philosophers[i].forks = params->forks;
	params->philosophers[i].print = params->print;
	params->philosophers[i].init_time = params->init_time;
	params->philosophers[i].dead = params->dead;
	params->philosophers[i].meals_completed = params->meals_completed;
	params->philosophers[i].min_meals = params->meals_nbr;
}
