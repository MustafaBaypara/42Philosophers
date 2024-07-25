/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:47:50 by mbaypara          #+#    #+#             */
/*   Updated: 2024/07/25 15:28:53 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdio.h>

static	int	check_death(t_vars *vars, int i)
{
	if (vars->philo[i].time_of_death
		<= get_time_micro())
	{
		vars->all_alive = 0;
		printf("%-6ld %d died\n",
			get_time() - vars->start_sim, vars->philo[i].id);
		pthread_mutex_unlock(vars->philo[i].left_fork);
		pthread_mutex_unlock(vars->alive);
		return (1);
	}
	return (0);
}

static	void	*check_on_philos(void *arg)
{
	t_vars			*vars;
	int				i;

	vars = (t_vars *)arg;
	while (1)
	{
		i = 0;
		while (i < vars->num_philo)
		{
			if (check_death(vars, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

static	void	init_time_of_death(t_philo *philo)
{
	long			time;

	time = get_time_micro();
	philo->time_of_death = time + (philo->vars->time_to_die * 1000);
}

static	void	*philosopher_dines(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	init_time_of_death(philo);
	if (philo->id % 2 == 0)
		ft_usleep(philo->vars->time_to_eat / 4);
	while (1)
	{
		if (take_forks(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (print_msg("is thinking", philo))
			return (NULL);
	}
}

int	create_threads(pthread_t *checking, pthread_t *newt, t_vars *vars)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&vars->flag, NULL))
		return (1);
	pthread_mutex_lock(&vars->flag);
	while (i < vars->num_philo)
	{
		if (pthread_create(&newt[i], NULL, &philosopher_dines, &vars->philo[i]))
			return (1);
		i++;
	}
	vars->start_sim = get_time();
	pthread_mutex_unlock(&vars->flag);
	if (pthread_create(checking, NULL, &check_on_philos, vars))
		return (1);
	return (0);
}
