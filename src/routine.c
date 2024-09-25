/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 22:36:07 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->ate == 1)
		return (pthread_mutex_unlock(&philo->key_mutex), 1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->key_mutex);
		if (!if_eat(philo))
			return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->key_mutex);
		if (!else_eat(philo))
			return (0);
	}
	return (1);
}

int	sleepy(t_philo *philo)
{
	long	time;

	print_action(philo, SLEEP);
	pthread_mutex_lock(&philo->key_mutex);
	time = (philo->data->sleep_time);
	pthread_mutex_unlock(&philo->key_mutex);
	waiter(time);
	return (1);
}

int	thinky(t_philo *philo)
{
	print_action(philo, THINK);
	waiter_white(philo);
	return (1);
}
