/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:24:04 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/04 17:36:54 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_params(t_params *params)
{
	if (params->limits)
		free(params->limits);
	if (params->forks)
		free(params->forks);
	if (params->philosophers)
		free(params->philosophers);
	free(params);
}
