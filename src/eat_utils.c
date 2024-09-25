/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:35:43 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 23:01:58 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_utils(t_philo *philo)
{
	pthread_mutex_lock(&philo->key_mutex);
	philo->last_eat = time_get();
	pthread_mutex_unlock(&philo->key_mutex);
	print_action(philo, EAT);
	waiter(philo->data->eat_time);
	pthread_mutex_lock(&philo->key_mutex);
	if (philo->data->ac == 6)
		philo->nb_meals--;
	pthread_mutex_unlock(&philo->key_mutex);
}

int	if_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	eat_utils(philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (philo->data->ac == 6 && philo->nb_meals == 0)
		return (0);
	return (1);
}

int	else_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	print_action(philo, FORK);
	if (&philo->fork == &philo->next->fork)
		return (pthread_mutex_unlock(&philo->fork), one_died(philo), 0);
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	eat_utils(philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	if (philo->data->ac == 6 && philo->nb_meals == 0)
		return (0);
	return (1);
}
