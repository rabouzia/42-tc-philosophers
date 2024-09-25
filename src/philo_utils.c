/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:10:53 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 13:15:58 by rabouzia         ###   ########.fr       */
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
		return (0);
	}
	pthread_mutex_unlock(&philo->data->smn_died);
	return (1);
}

int	check_finished(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo)
	{
		// if (!check_dead(philo))
		// 	return (printf("died\n"),0);
		pthread_mutex_lock(&philo->key_mutex);
		if (!philo->nb_meals)
		{
			pthread_mutex_unlock(&philo->key_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->key_mutex);
		philo = philo->next;
		if (first == philo)
			break ;
	}
	return (1);
}

void	waiter(long time)
{
	long	start;

	start = time_get();
	while ((time_get() - start) < time)
		usleep(100);
}

int	print_action(t_philo *philo, char *str)
{
	long	time;

	time = time_get();
	pthread_mutex_lock(&philo->data->smn_died);
	if (!philo->data->is_dead)
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->smn_died);
	return (1);
}
