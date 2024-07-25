/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:29:46 by mbaypara          #+#    #+#             */
/*   Updated: 2024/06/30 22:36:36 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static	int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	philo->meals_eaten++;
	while (i < philo->vars->num_philo
		&& philo->vars->philo[i].meals_eaten >= philo->vars->num_meals)
		i++;
	if (i == philo->vars->num_philo)
	{
		philo->vars->all_full = 1;
		return (1);
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	if (print_msg("is eating", philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->vars->alive);
	philo->time_of_death = get_time_micro() + (philo->vars->time_to_die * 1000);
	if (philo->vars->num_meals != -1)
	{
		if (check_meals(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (pthread_mutex_unlock(philo->vars->alive), 1);
		}
	}
	pthread_mutex_unlock(philo->vars->alive);
	return (ft_usleep(philo->vars->time_to_eat), 0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo);
	if (eat(philo))
		return (1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (print_msg("is sleeping", philo))
		return (1);
	ft_usleep(philo->vars->time_to_sleep);
	return (0);
}
