/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 17:49:40 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->key_mutex);
	philo->last_eat = time_get();
	pthread_mutex_unlock(&philo->key_mutex);
	print_action(philo, EAT);
	waiter(philo->data->eat_time);
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->key_mutex);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (philo->data->ac == 6 && philo->nb_meals == 0)
		return (0);
	return (1);
}

void	one_died(t_philo *philo)
{
	waiter(philo->data->life_range);
	print_action(philo, DIED);
}

int	else_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	if (&philo->fork == &philo->next->fork)
		return (pthread_mutex_unlock(&philo->fork), one_died(philo), 0);
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->key_mutex);
	philo->last_eat = time_get();
	pthread_mutex_unlock(&philo->key_mutex);
	print_action(philo, EAT);
	waiter(philo->data->eat_time);
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->key_mutex);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	if (philo->data->ac == 6 && philo->nb_meals == 0)
		return (0);
	return (1);
}

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
