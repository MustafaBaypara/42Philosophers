/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:34 by mbaypara          #+#    #+#             */
/*   Updated: 2024/06/30 23:11:31 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <stdio.h>

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (sign * result);
}

static int	ft_isnotdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (ft_isnotdigit(argv[1]) || ft_isnotdigit(argv[2])
		|| ft_isnotdigit(argv[3]) || ft_isnotdigit(argv[4]))
		return (printf("Error: Please provide only digits\n"), 1);
	if (check_size(argv))
		return (printf("Error: Only positive integers are allowed\n"), 1);
	if (ft_atoi(argv[1]) < 1)
		return (printf("Error: Please specify at least 1 philosopher\n"), 1);
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (printf("Error: Args mustn't be negative\n"), 1);
	if (argc == 6)
	{
		if (*argv[5] == '0')
			return (1);
		if (ft_strlen(argv[5]) > 10
			|| ft_strlen(argv[5]) != num_len(ft_atoi(argv[5])))
			return (printf("Error: Only positive integers are allowed\n"), 1);
		if (ft_atoi(argv[5]) < 0)
			return (printf("Error: Args mustn't be negative\n"), 1);
		if (ft_isnotdigit(argv[5]))
			return (printf("Error: Please provide digits\n"), 1);
	}
	return (0);
}

int	print_msg(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->vars->alive);
	if (!(philo->vars->all_alive) || philo->vars->all_full)
		return (pthread_mutex_unlock(philo->vars->alive), 1);
	printf("%-6ld %d %s\n",
		get_time() - philo->vars->start_sim, philo->id, str);
	pthread_mutex_unlock(philo->vars->alive);
	return (0);
}
