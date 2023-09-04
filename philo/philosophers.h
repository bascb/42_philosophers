/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:02 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/04 10:14:59 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_limits
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
}					t_limits;

typedef struct s_philo
{
	unsigned int	philo_nbr;
	unsigned int	nbr_of_philos;
	t_limits		*limits;
	unsigned char	*forks;
	unsigned long	last_eat_start;
	unsigned long	last_sleep_start;
	int				meals_nbr;
}					t_philo;

typedef struct s_params
{
	t_limits		*limits;
	unsigned int	nbr_of_philos;
	unsigned char	*forks;
	t_philo			*philosophers;
}					t_params;

unsigned long	get_current_time(void);

void			*ft_calloc(size_t nmemb, size_t size);

t_params		*get_params(int argc, char **argv);

unsigned int	ft_atou(const char *num_str);

unsigned long	ft_atoul(const char *num_str);

void			print_help(char **argv);

#endif