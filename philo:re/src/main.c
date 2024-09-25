/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 00:31:04 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *tada)
{
	t_philo	*philo;
	t_data	*data;


	data = (t_data *)tada;
	philo = data->philo;
	
	if (philo->id % 2 == 0)
		waiter(1);
	while (1)
	{
		if (data->ac == 6)
		{
			if (!check_finished(philo, data))
				break ;
		}
		if (!check_dead(data))
			break ;
		if (!eat(philo, data))
			break ;
		if (!sleepy(philo, data))
			break ;
		if (!thinky(philo, data))
			break ;
	}
	return (0);
}

int	monitoring(t_philo *philo, t_data *data)
{
	long	time;
	t_philo	*first;

	first = philo;
	time = time_get();
	while (philo)
	{
		pthread_mutex_lock(&philo->fork);
 		pthread_mutex_lock(&data->smn_died);
		if (time - philo->last_eat > data->life_range && data->is_dead == 0 )
		{
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_lock(&data->smn_died);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->smn_died);
			pthread_mutex_unlock(&data->smn_died);
			printf("%li %d %s\n", time - data->start_time, philo->id, DIED);
			pthread_mutex_unlock(&data->smn_died);
			return (0);
 		}
		pthread_mutex_unlock(&philo->fork);
 		pthread_mutex_unlock(&data->smn_died);
 		philo = philo->next;
		if (data->ac == 6)
		{
			if (check_finished(philo, data))
				return (0);
		}
 		if (first == philo)
 			break ;
	}
	return (1);
}

void	thread_join(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		pthread_join(tmp->pid, NULL);
		tmp = tmp->next;
		if (tmp == philo)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;

	bzero(&data, sizeof(t_data));
	bzero(&philo, sizeof(t_philo));
	if (!(ac == 5 || ac == 6))
		return (write(2, "Error\nWrong number of arguments\n", 32), 0);
	if (!check_av(av + 1))
		return (0);
	init_args(ac, av + 1, &philo, &data);
	while (1)
	{
		if (!monitoring(&philo, &data))
			break ;
	}
	thread_join(&philo);
	tornado_wipe(&philo);
	return (0);
}
