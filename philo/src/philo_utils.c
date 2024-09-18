/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:10:53 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/18 15:38:19 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_get(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->smn_died);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->smn_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->smn_died);
	return (0);
}

int	waiter(long time)
{
	int	i;

	i = 0;
	while (i++ < time / 10)
		usleep(10);
	return (1);
}

int	print_action(t_philo *philo, char *str)
{
	long	time;

	time = time_get();
	pthread_mutex_lock(&philo->data->smn_died);
	if (time - philo->last_eat > philo->data->life_range
		&& philo->data->is_dead == 0)
	{
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->smn_died);
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, DIED);
		return (0);
	}
	if (!philo->data->is_dead)
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->smn_died);
	return (1);
}
