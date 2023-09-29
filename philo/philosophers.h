/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:02 by bcastelo          #+#    #+#             */
/*   Updated: 2023/09/28 21:57:51 by bcastelo         ###   ########.fr       */
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

# define EATING 0
# define SLEEPING 1
# define THINKING 2  

typedef struct s_limits
{
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	start_time;
}					t_limits;

typedef struct s_philo
{
	unsigned int		philo_nbr;
	unsigned int		state;
	pthread_t			id;
	pthread_mutex_t		*mtx;
	void				*res;
	unsigned int		nbr_of_philos;
	unsigned int		*sim_state;
	t_limits			*limits;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	unsigned long		last_eat_start;
	unsigned long		last_sleep_start;
	unsigned int		meals_nbr;
}						t_philo;

typedef struct s_params
{
	t_limits			*limits;
	unsigned int		nbr_of_philos;
	unsigned int		meals_nbr;
	unsigned int		sim_state;
	pthread_mutex_t		*forks;
	t_philo				*philosophers;
	pthread_mutex_t		mtx;
}					t_params;

void			create_philosophers(t_params *params);

void			control_simulation(t_params *params);

void			*manage_gathering(void *arg);

unsigned long	get_current_time(void);

int				check_timeout(unsigned long start, unsigned long timeout);

void			*ft_calloc(size_t nmemb, size_t size);

t_params		*get_params(int argc, char **argv);

void			set_philo_data(t_params *params, int i);

t_params		*clean_params(t_params *params);

unsigned int	ft_atou(const char *num_str);

unsigned long	ft_atoul(const char *num_str);

int				is_alive(unsigned long last_meal, unsigned long time_to_die);

void			print_log(t_philo *data, char *msg);

void			print_help(char **argv);

#endif