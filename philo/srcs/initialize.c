/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:49:45 by mbaypara          #+#    #+#             */
/*   Updated: 2024/06/30 23:11:03 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdlib.h>

static	t_vars	*allocate(int num_philo)
{
	t_vars	*vars;

	vars = calloc(1, sizeof(*vars));
	if (!vars)
		return (NULL);
	vars->forks = calloc(num_philo, sizeof((*(vars->forks))));
	if (!(vars->forks))
		return (NULL);
	vars->philo = calloc(num_philo, sizeof(*(vars->philo)));
	if (!(vars->philo))
		return (NULL);
	vars->alive = calloc(1, sizeof(*(vars->alive)));
	if (!(vars->alive))
		return (NULL);
	return (vars);
}

static	int	set_vars(t_vars *vars, char **argv, int num_philo)
{
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		vars->num_meals = ft_atoi(argv[5]);
	else
		vars->num_meals = -1;
	vars->num_philo = num_philo;
	vars->all_full = 0;
	vars->start_sim = 0;
	vars->all_alive = 1;
	return (0);
}

static	int	init_philos(t_vars *vars, int num_philo)
{
	int				i;

	i = 0;
	while (i < num_philo)
	{
		vars->philo[i].vars = vars;
		vars->philo[i].id = i + 1;
		vars->philo[i].meals_eaten = 0;
		vars->philo[i].left_fork = &vars->forks[i];
		if (i + 1 == num_philo)
			vars->philo[i].right_fork = &vars->forks[0];
		else
			vars->philo[i].right_fork = &vars->forks[i + 1];
		i++;
	}
	return (0);
}

static	t_vars	*init_structs(char **argv, int num_philo)
{
	t_vars	*vars;
	int		i;

	i = 0;
	vars = allocate(num_philo);
	if (!vars)
		return (NULL);
	if (set_vars(vars, argv, num_philo))
		return (free(vars), NULL);
	while (i < num_philo)
		if (pthread_mutex_init(&vars->forks[i++], NULL))
			return (free(vars), NULL);
	if (pthread_mutex_init(vars->alive, NULL))
		return (free(vars), NULL);
	if (pthread_mutex_init(&vars->time_m, NULL))
		return (free(vars), NULL);
	init_philos(vars, num_philo);
	return (vars);
}

int	init_vars(pthread_t **checking, pthread_t **newt, char **av, t_vars **vars)
{
	int	num_philo;

	num_philo = ft_atoi(av[1]);
	*checking = malloc(sizeof(**checking));
	if (!(*checking))
		return (1);
	*newt = malloc(num_philo * sizeof(**newt));
	if (!(*newt))
		return (1);
	*vars = init_structs(av, num_philo);
	if (!(*vars))
		return (1);
	return (0);
}
