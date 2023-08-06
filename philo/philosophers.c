/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:32:40 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/06 15:14:07 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(void)
{
	unsigned long	first;
	unsigned long	second;
	unsigned long	diff;

	first = get_current_time();
	usleep(100000);
	second = get_current_time();
	diff = second - first;
	printf("Let's think! %lu\n", diff);
	return (0);
}
