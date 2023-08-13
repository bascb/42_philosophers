/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:51:38 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/13 12:48:02 by bcastelo         ###   ########.fr       */
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

int	get_params(int argc, char **argv)
{
	t_params	*params;
	
	if (check_params(argc, argv) == -1)
		return (NULL);
	params = ft_calloc(1, sizeof(t_params));
	if (params == NULL)
		return (NULL);
	params->nbr_of_philos = ft_atou(argv[1]);
	return (params);
}