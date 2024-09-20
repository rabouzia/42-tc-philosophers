/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:08:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/20 15:25:51 by rabouzia         ###   ########.fr       */
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
	philo->nb_meals--;
	pthread_mutex_unlock(&cur->fork);
	pthread_mutex_unlock(&cur->next->fork);
}

void	else_eat(t_philo *philo, t_philo *cur)
{
	if(&cur->fork == &cur->next->fork)
		return;
	pthread_mutex_lock(&cur->next->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&cur->fork);
	print_action(philo, FORK);
	print_action(philo, EAT);
	philo->last_eat = time_get();
	waiter(philo->data->eat_time);
	philo->nb_meals--;
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
	// if ((philo->data->nb_philo % 2 ==0) && (philo->data->eat_time > philo->data->sleep_time))
	// 	waiter(philo->data->eat_time - philo->data->sleep_time);
		// if(philo->data->nb_philo % 2 != 0)
		// 	waiter(700);
	return (1);
}
