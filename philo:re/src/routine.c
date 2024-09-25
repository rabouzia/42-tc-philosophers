/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 00:26:24 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	if_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo,data, FORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo,data, FORK);
	print_action(philo,data, EAT);
	philo->last_eat = time_get();
	waiter(data->eat_time);
	if (data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	else_eat(t_philo *philo , t_data *data)
{
	if (&philo->fork == &philo->next->fork)
		return ;
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, data, FORK);
	pthread_mutex_lock(&philo->fork);
	print_action(philo,data, FORK);
	print_action(philo,data, EAT);
	philo->last_eat = time_get();
	waiter(data->eat_time);
	if (data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

int	eat(t_philo *philo, t_data *data)
{
	if (philo->ate == 1)
		return (1);
	if (philo->id % 2 == 0)
		if_eat(philo, data);
	else
		else_eat(philo, data);
	return (1);
}

int	sleepy(t_philo *philo, t_data *data)
{
	print_action(philo, data, SLEEP);
	waiter(data->sleep_time);
	return (1);
}

int	thinky(t_philo *philo, t_data *data)
{
	print_action(philo,data, THINK);
	if (data->nb_philo % 2 != 0)
		waiter(50);
	return (1);
}
