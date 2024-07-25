/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:56:55 by mbaypara          #+#    #+#             */
/*   Updated: 2024/07/01 00:41:33 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_vars	t_vars;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			time_of_death;
	int				meals_eaten;
	t_vars			*vars;
}				t_philo;

typedef struct s_vars
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_philo;
	int				all_alive;
	int				all_full;
	int				num_meals;
	pthread_mutex_t	flag;
	long			start_sim;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*alive;
	pthread_mutex_t	time_m;
}				t_vars;

int		ft_atoi(const char *str);
int		check_args(int argc, char **argv);
int		print_msg(char *str, t_philo *philo);
long	get_time(void);
long	get_time_micro(void);
int		ft_usleep(int wait);
int		take_forks(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		init_vars(pthread_t **checking, pthread_t **thread,
			char **argv, t_vars **vars);
int		create_threads(pthread_t *checking, pthread_t *thread, t_vars *vars);
void	free_mem(t_vars *vars, pthread_t *thread, pthread_t *checking);
int		ft_strlen(const char *s);
int		num_len(int i);
int		check_size(char **argv);

#endif