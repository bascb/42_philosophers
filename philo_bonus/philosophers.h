/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:19:02 by bcastelo          #+#    #+#             */
/*   Updated: 2023/10/18 19:58:31 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>

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
	pid_t				id;
	unsigned int		nbr_of_philos;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*init_time;
	sem_t				*dead;
	sem_t				*meals_completed;
	unsigned int		*sim_state;
	t_limits			*limits;
	unsigned long		start_time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		last_eat_start;
	unsigned long		last_sleep_start;
	unsigned int		min_meals;
	unsigned int		meals_nbr;
}						t_philo;

typedef struct s_params
{
	t_limits			*limits;
	unsigned int		nbr_of_philos;
	unsigned int		meals_nbr;
	unsigned int		sim_state;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*init_time;
	sem_t				*dead;
	sem_t				*meals_completed;
	t_philo				*philosophers;
}					t_params;

void			create_philosophers(t_params *params);

void			control_simulation(t_params *params);

void			*manage_gathering(void *arg);

unsigned long	get_current_time(void);

int				check_timeout(unsigned long start, unsigned long timeout);

void			*ft_calloc(size_t nmemb, size_t size);

t_params		*get_params(int argc, char **argv);

int				create_semaphores(t_params *params);

void			set_philo_data(t_params *params, int i);

t_params		*clean_params(t_params *params);

unsigned int	ft_atou(const char *num_str);

unsigned long	ft_atoul(const char *num_str);

void			print_log(t_philo *data, char *msg);

void			print_help(char **argv);

#endif