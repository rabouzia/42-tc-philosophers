/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:10:53 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 23:05:36 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_av(char **av)
{
	short	i;
	short	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (ft_atoi(av[0]) < 1)
		return (0);
	return (1);
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

int	dead_verif(t_philo *philo)
{
	long	time;

	time = time_get();
	pthread_mutex_lock(&philo->key_mutex);
	if (time - philo->last_eat >= philo->data->life_range)
	{
		pthread_mutex_unlock(&philo->key_mutex);
		pthread_mutex_lock(&philo->data->smn_died);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->smn_died);
		printf("%li %d %s\n", time - philo->data->start_time, philo->id,
			DIED);
		return (0);
	}
	pthread_mutex_unlock(&philo->key_mutex);
	return (1);
}
