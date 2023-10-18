/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:03:49 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/18 19:55:22 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_params(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_all_digits(argv[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	create_semaphores(t_params *params)
{
	params->print = sem_open("/print", O_CREAT, 0, 1);
	if (params->print == SEM_FAILED)
	{
		clean_params(params);
		return (0);
	}
	params->init_time = sem_open("/time", O_CREAT, 0, 0);
	if (params->init_time == SEM_FAILED)
	{
		clean_params(params);
		return (0);
	}
	params->dead = sem_open("/dead", O_CREAT, 0, 0);
	if (params->dead == SEM_FAILED)
	{
		clean_params(params);
		return (0);
	}
	params->meals_completed = sem_open("/meals", O_CREAT, 0, 0);
	if (params->meals_completed == SEM_FAILED)
	{
		clean_params(params);
		return (0);
	}
	return (1);
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
