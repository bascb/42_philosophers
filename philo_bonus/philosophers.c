/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:32:40 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/17 22:31:27 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_childs(t_params *params);

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
	pid_t			id;

	i = 0;
	while (i < params->nbr_of_philos)
		set_philo_data(params, i++);
	i = 0;
	while (i < params->nbr_of_philos)
	{
		id = fork();
		if (id == -1)
		{
			kill_childs(params);
			clean_params(params);
			exit(1);
		}
		if (id == 0)
			manage_gathering(&params->philosophers[i]);
		else
			params->philosophers[i].id = id;
		i++;
	}
	sem_post(params->init_time);
}

void	control_simulation(t_params *params)
{
	sem_wait(params->dead);
	kill_childs(params);
}

void	kill_childs(t_params *params)
{
	unsigned int	i;

	i = 0;
	while (i < params->nbr_of_philos)
	{
		if (params->philosophers[i].id)
			kill(params->philosophers[i].id, 9);
		i++;
	}
}
