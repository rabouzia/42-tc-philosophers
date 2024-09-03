/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/03 16:34:14 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	t_philo	*cur;

	cur = philo;
	pthread_mutex_lock(&cur->fork);
	if (cur->next == NULL)
		pthread_mutex_lock(&philo->fork);
	else
		pthread_mutex_lock(&cur->next->fork);
	usleep(philo->data->eat_time);
	cur->ate = 1;
	pthread_mutex_unlock(&cur->fork);
	if (cur->next == NULL)
		pthread_mutex_unlock(&philo->fork);
	else
		pthread_mutex_unlock(&cur->next->fork);
	return (1);
}

int	check_dead(t_philo *philo)
{
	while (philo)
	{
		if (philo->is_dead == 1)
			return (1);
		philo = philo->next;
	}
	return (0);
}

int	waiter(t_philo *philo, long time)
{
	int	i;

	i = 0;
	while (i <= (time / 10))
	{
		usleep(10);
		if (check_dead(philo) == 1)
			return (0);
		i++;
	}
	return (1);
}

void	*routine(void *lophi)
{
	t_philo	*philo;

	philo = (t_philo *)lophi;
	while (1)
	{
		if (!eat(philo))
			break ;
		// if (!sleep())
		// 	break ;
		check_dead(philo);
	}
	return(0);
}

void	print_timestamp(t_philo *philo, t_data *data)
{
	printf("%li %d %s\n", data->start_time, philo->id, EAT);
	philo = philo->next;
	printf("%li %d %s\n", data->start_time, philo->id, EAT);
	philo = philo->next;
	printf("%li %d %s\n", data->start_time, philo->id, EAT);
}

int	main(int ac, char **av)
{
	t_data data;
	t_philo *philo;

	philo = NULL;
	bzero(&data, sizeof(t_data));
	if (!(ac == 5 || ac == 6))
		return (write(2, "Error\nWrong number of arguments\n", 32), 0);
	if (!check_av(av + 1))
		return (0);
	init_args(ac, av + 1, &philo, &data);
	printf("time get :%li\n", data.start_time);
	free(philo);
	return (0);
}