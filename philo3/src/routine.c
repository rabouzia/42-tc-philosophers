/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 00:04:36 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	if_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = time_get();
	pthread_mutex_unlock(&philo->eating);
	waiter(philo->data->eat_time);
	pthread_mutex_lock(&philo->mutex);
	if (philo->data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	else_eat(t_philo *philo)
{
	if (&philo->fork == &philo->next->fork)
		return ;
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = time_get();
	pthread_mutex_unlock(&philo->eating);
	waiter(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->all_finished);
	pthread_mutex_lock(&philo->mutex2);
	if (philo->data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->data->all_finished);
	pthread_mutex_unlock(&philo->mutex2);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

int	eat(t_philo *philo)
{
	if (philo->ate == 1)
		return (1);
	if (philo->id % 2 == 0)
		if_eat(philo);
	else
		else_eat(philo);
	return (1);
}

int	sleepy(t_philo *philo)
{
	print_action(philo, SLEEP);
	waiter(philo->data->sleep_time);
	return (1);
}

int	thinky(t_philo *philo)
{
	print_action(philo, THINK);
	// if ((philo->data->nb_philo % 2 == 0)
	// 	&& (philo->data->eat_time > philo->data->sleep_time))
	// 	waiter(philo->data->eat_time - philo->data->sleep_time);
		// waiter(50);
	if (philo->data->nb_philo % 2 != 0)
		waiter(50);
	// waiter(50);
	return (1);
}
