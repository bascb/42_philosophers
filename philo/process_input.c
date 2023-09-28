/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:51:38 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/27 20:38:13 by bcastelo         ###   ########.fr       */
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
	params->forks = ft_calloc(params->nbr_of_philos, sizeof(pthread_mutex_t));
	if (!params->philosophers || !params->forks)
	{
		printf("Unable to alloc memory for forks or philosophers\n");
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
	if (pthread_mutex_init(&params->mtx, NULL))
		return (clean_params(params));
	return (params);
}

void	set_philo_data(t_params *params, int i)
{
	params->philosophers[i].philo_nbr = i + 1;
	params->philosophers[i].nbr_of_philos = params->nbr_of_philos;
	params->philosophers[i].sim_state = &params->sim_state;
	params->philosophers[i].limits = params->limits;
	if (params->nbr_of_philos > 1)
	{
		if (i + 1 == (int) params->nbr_of_philos)
			params->philosophers[i].right = &params->forks[0];
		else
			params->philosophers[i].right = &params->forks[i + 1];
		params->philosophers[i].left = &params->forks[i];
	}
	params->philosophers[i].meals_nbr = params->meals_nbr;
	params->philosophers[i].mtx = &params->mtx;
}
