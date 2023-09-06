/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:32:40 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/06 14:05:15 by bcastelo         ###   ########.fr       */
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
	params->sim_state = 1;
	params->limits->start_time = get_current_time();
	i = 0;
	while (i < params->nbr_of_philos)
	{
		pthread_join(params->philosophers[i].id, params->philosophers[i].res);
		i++;
	}
}

void	print_help(char **argv)
{
	char	*help[5];
	int		i;

	help[0] = "number_of_philosophers";
	help[1] = "time_to_die";
	help[2] = "time_to_eat";
	help[3] = "time_to_sleep";
	help[4] = "[number_of_times_each_philosopher_must_eat]";
	printf("usage: %s", argv[0]);
	i = 0;
	while (i < 5)
		printf(" %s", help[i++]);
	printf("\n");
}
