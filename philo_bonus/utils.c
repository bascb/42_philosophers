/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:03:52 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/19 10:02:43 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_current_time(void)
{
	struct timeval	tv;
	unsigned long	milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (milliseconds);
}

int	check_timeout(unsigned long start, unsigned long timeout)
{
	unsigned long	now;

	now = get_current_time();
	if (now <= start + timeout)
		return (0);
	return (1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	if (!nmemb || !size)
		return (ptr);
	memset(ptr, 0, nmemb * size);
	return (ptr);
}

unsigned int	ft_atou(const char *num_str)
{
	int				i;
	unsigned int	result;

	result = 0;
	i = 0;
	while (num_str[i] >= '0' && num_str[i] <= '9')
	{
		result = result * 10 + (num_str[i] - '0');
		i++;
	}
	return (result);
}

unsigned long	ft_atoul(const char *num_str)
{
	int				i;
	unsigned long	result;

	result = 0;
	i = 0;
	while (num_str[i] >= '0' && num_str[i] <= '9')
	{
		result = result * 10 + (num_str[i] - '0');
		i++;
	}
	return (result);
}
