/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:32:40 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/04 10:12:54 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	unsigned char	*forks;
	unsigned long	first;
	unsigned long	second;
	unsigned long	diff;

	(void) forks;
	if (argc < 5)
	{
		print_help(argv);
		return (0);
	}
	first = get_current_time();
	usleep(100000);
	second = get_current_time();
	diff = second - first;
	printf("Let's think! %lu\n", diff);
	return (0);
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
