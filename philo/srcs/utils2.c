/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:20:46 by mbaypara          #+#    #+#             */
/*   Updated: 2024/07/25 15:29:40 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

void	free_mem(t_vars *vars, pthread_t *newthread, pthread_t *checking)
{
	if (vars)
		free(vars);
	if (newthread)
		free(newthread);
	if (checking)
		free(checking);
}

int	ft_usleep(int wait)
{
	long	start;

	start = get_time();
	while (get_time() < start + wait)
		usleep(500);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

long	get_time_micro(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000 + tv.tv_usec));
}
