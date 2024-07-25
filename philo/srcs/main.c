/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:22:09 by mbaypara          #+#    #+#             */
/*   Updated: 2024/07/01 00:56:07 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	num_len(int i)
{
	int	len;

	len = 0;
	while (i > 0)
	{
		len++;
		i /= 10;
	}
	return (len);
}

int	check_size(char **argv)
{
	if (ft_strlen(argv[1]) > 10 || ft_strlen(argv[2]) > 10
		|| ft_strlen(argv[3]) > 10 || ft_strlen(argv[4]) > 10)
		return (1);
	if (ft_strlen(argv[1]) != num_len(ft_atoi(argv[1]))
		|| ft_strlen(argv[2]) != num_len(ft_atoi(argv[2]))
		|| ft_strlen(argv[3]) != num_len(ft_atoi(argv[3]))
		|| ft_strlen(argv[4]) != num_len(ft_atoi(argv[4])))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	*newthread;
	pthread_t	*checking;
	t_vars		*vars;
	int			i;

	if (argc < 5 || argc > 6)
		return (printf("Please enter 4-5 arguments.\n"), 1);
	if (check_args(argc, argv))
		return (1);
	i = 0;
	if (init_vars(&checking, &newthread, argv, &vars))
		return (free_mem(vars, newthread, checking), 1);
	if (create_threads(checking, newthread, vars))
		return (free_mem(vars, newthread, checking), 1);
	while (i < vars->num_philo)
		if (pthread_join(newthread[i++], NULL))
			return (free_mem(vars, newthread, checking), 1);
	i = 0;
	while (i < vars->num_philo)
		if (pthread_mutex_destroy(&(vars->forks[i++])))
			return (free_mem(vars, newthread, checking), 1);
	if (pthread_mutex_destroy(vars->alive))
		return (free_mem(vars, newthread, checking), 1);
	if (pthread_mutex_destroy(&vars->time_m))
		return (free_mem(vars, newthread, checking), 1);
	free_mem(vars, newthread, checking);
}
