/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/17 23:25:59 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->smn_died);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->smn_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->smn_died);
	return (0);
}

// int	waiter(t_philo *philo, long time)
// {
// 	while (i  < time)
// 	{
// 		usleep(10);
// 		i++;
// 	}
// 	return (1);
// }

int	print_action(t_philo *philo, char *str)
{
	long	time;

	time = time_get();
	// check le temps de la derniere fois ou il manger
	// somedied
	pthread_mutex_lock(&philo->data->smn_died);
	if (time - philo->last_eat > philo->data->life_range
		&& philo->data->is_dead == 0)
	{
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->smn_died);
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, DIED);
		return (0);
	}
	if (!philo->data->is_dead)
		printf("%li %d %s\n", time - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->smn_died);
	return (1);
}

int	eat(t_philo *philo)
{
	t_philo	*cur;

	cur = philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&cur->fork);
		print_action(philo, FORK);
		pthread_mutex_lock(&cur->next->fork);
		print_action(philo, FORK);
		print_action(philo, EAT);
		philo->last_eat = time_get();
		usleep(philo->data->eat_time * 1000);
		pthread_mutex_unlock(&cur->fork);
		pthread_mutex_unlock(&cur->next->fork);
	}
	else
	{
		pthread_mutex_lock(&cur->next->fork);
		print_action(philo, FORK);
		pthread_mutex_lock(&cur->fork);
		print_action(philo, FORK);
		print_action(philo, EAT);
		philo->last_eat = time_get();
		usleep(philo->data->eat_time * 1000);
		pthread_mutex_unlock(&cur->next->fork);
		pthread_mutex_unlock(&cur->fork);
	}
	return (1);
}

int	sleepy(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->data->sleep_time * 1000);
	return (1);
}

int	thinky(t_philo *philo)
{
	print_action(philo, THINK);
	return (1);
}

void	*routine(void *lophi)
{
	t_philo	*philo;

	philo = (t_philo *)lophi;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_dead(philo))
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

void	print_timestamp(t_philo *philo, t_data *data)
{
	printf("%li %d %s\n", data->start_time, philo->id, EAT);
	philo = philo->next;
	printf("%li %d %s\n", data->start_time, philo->id, EAT);
	philo = philo->next;
	printf("%li %d %s\n", data->start_time, philo->id, EAT);
}

// void	mr_propre(t_list **lst)
// {
// 	t_list	*tmp;
// 	t_list	*head;

// 	head = *lst;
// 	if (!lst || !*lst)
// 		return ;
// 	while (*lst)
// 	{
// 		tmp = (*lst)->next;
// 		ft_lstdelone(*lst);
// 		*lst = tmp;
// 		if (*lst == head)
// 			break ;
// 	}
// }

void	ft_lstdelone(t_philo *lst)
{
	if (!lst)
		return ;
	if (lst)
		free(lst);
}

void	tornado_wipe(t_philo *philo)
{
	t_philo	*first;
	t_philo	*tmp;

	printf("wipey\n");
	first = philo;
	philo = philo->next;
	while (philo)
	{
		tmp = philo->next;
		printf("philo %d is washing his plate\n\n\n", philo->id);
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		philo = tmp;
		if (philo == first)
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
	tornado_wipe(&philo);
	return (0);
}
