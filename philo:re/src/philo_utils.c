/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:10:53 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 00:30:36 by ramzerk          ###   ########.fr       */
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

int	check_dead(t_data *data)
{
	pthread_mutex_lock(&data->smn_died);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->smn_died);
		return (0);
	}
	pthread_mutex_unlock(&data->smn_died);
	return (1);
}

int	check_finished(t_philo *philo, t_data *data)
{
	t_philo	*first;

	first = philo;
	while (philo)
	{
		pthread_mutex_lock(&data->all_finished);
		pthread_mutex_lock(&philo->fork);
 		if (!philo->nb_meals)
 		{
			pthread_mutex_unlock(&data->all_finished);
			pthread_mutex_unlock(&philo->fork);
 			return (0);
 		}
		pthread_mutex_unlock(&data->all_finished);
		pthread_mutex_unlock(&philo->fork);
 		philo = philo->next;
 		if (first == philo)
 			break ;
	}
	pthread_mutex_unlock(&data->all_finished);
	return (1);
}

void	waiter(long time)
{
	long	start;

	start = time_get();
	while ((time_get() - start) < time)
		usleep(10);
}

int	print_action(t_philo *philo, t_data *data, char *str)
{
	
	long time = time_get();
 	pthread_mutex_lock(&data->smn_died);
	// pthread_mutex_lock(&philo->data->all_finished);
 	if (!data->is_dead)
	{
 		printf("%li %d %s\n", time - data->start_time, philo->id, str);
	}
	// pthread_mutex_unlock(&philo->data->all_finished);
 	pthread_mutex_unlock(&data->smn_died);
 	return (1);
}
