/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 23:04:12 by ramzerk          ###   ########.fr       */
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
	t_philo	*first;
	int		i;

	first = philo;
	i = 1;
	while (philo)
	{
		pthread_mutex_lock(&philo->key_mutex);
		if (philo->nb_meals == 0 && philo->data->ac == 6)
			i++;
		pthread_mutex_unlock(&philo->key_mutex);
		if (!dead_verif(philo))
			return (0);
		philo = philo->next;
		if (i == philo->data->nb_philo && philo->data->ac == 6)
			return (0);
		if (first == philo)
			break ;
	}
	return (1);
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
	if (!init_args(ac, av + 1, &philo, &data))
		return (0);
	while (1)
	{
		if (!monitoring(&philo))
			break ;
	}
	if (!thread_join(&philo))
		return (0);
	tornado_wipe(&philo);
	return (0);
}
