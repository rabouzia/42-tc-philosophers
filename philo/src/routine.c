/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/18 17:46:26 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	if_eat(t_philo *philo, t_philo *cur)
{
	pthread_mutex_lock(&cur->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&cur->next->fork);
	print_action(philo, FORK);
	print_action(philo, EAT);
	philo->last_eat = time_get();
	waiter(philo->data->eat_time);
	pthread_mutex_unlock(&cur->fork);
	pthread_mutex_unlock(&cur->next->fork);
}

void	else_eat(t_philo *philo, t_philo *cur)
{
	pthread_mutex_lock(&cur->next->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&cur->fork);
	print_action(philo, FORK);
	print_action(philo, EAT);
	philo->last_eat = time_get();
	waiter(philo->data->eat_time);
	pthread_mutex_unlock(&cur->next->fork);
	pthread_mutex_unlock(&cur->fork);
}

int	eat(t_philo *philo)
{
	t_philo	*cur;

	cur = philo;
	if (philo->id % 2 == 0)
		if_eat(philo, cur);
	else
		else_eat(philo, cur);
	philo->nb_meals--;
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
	return (1);
}
