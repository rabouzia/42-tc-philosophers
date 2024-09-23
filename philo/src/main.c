/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/23 15:30:45 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *lophi)
{
	t_philo	*philo;

	philo = (t_philo *)lophi;
	if (philo->id % 2 == 0)
		waiter(1);
	while (1)
	{
		if (philo->data->ac == 6)
		{
			if (!check_finished(philo))
				break ;
		}
		if (!check_dead(philo))
			break ;
		if (!eat(philo))
			break ;
		if (!sleepy(philo))
			break ;
		if (!thinky(philo))
			break ;
	}
	return (0);
}

int	monitoring(t_philo *philo)
{
	long	time;
	t_philo	*first;

	first = philo;
	time = time_get();
	while (philo)
	{
		pthread_mutex_lock(&philo->data->smn_died);
		if (time - philo->last_eat > philo->data->life_range
			&& philo->data->is_dead == 0)
		{
			philo->data->is_dead = 1;
			pthread_mutex_unlock(&philo->data->smn_died);
			printf("%li %d %s\n", time - philo->data->start_time, philo->id,
				DIED);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->smn_died);
		philo = philo->next;
		if (check_finished(philo))
			return (0);
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
		if (!monitoring(&philo))
			break ;
	}
	thread_join(&philo);
	tornado_wipe(&philo);
	return (0);
}
