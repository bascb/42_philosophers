/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:51:38 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/04 17:16:22 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_digits(char *str);

int	check_params(int argc, char **argv);

int	get_nbr_of_philos(t_params *params, char *str)
{
	unsigned int	nbr;

	nbr = ft_atou(str);
	if (nbr > 200)
	{
		printf("Number of philosophers (%d) exceeds the limit of 200\n", nbr);
		return (0);
	}
	params->nbr_of_philos = nbr;
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
		return (NULL);
	return (params);
}
