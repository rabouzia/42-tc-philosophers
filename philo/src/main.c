/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/07 22:03:00 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (time_get() - philo->data->start_time < time)
	{
		usleep(100);
	}
	return (1);
}

int	print_action(t_philo *philo, char *str)
{
	long	time;

	time = time_get();
	printf("%li %d %s\n", time - philo->data->start_time, philo->id, str);
	return (1);
}

int	eat(t_philo *philo)
{
	t_philo	*cur;

	cur = philo;
	// printf("eat\n");
	if (philo->id % 2 == 0)
	{
		// printf("time is %li", time_get() - philo->data->start_time);
		pthread_mutex_lock(&cur->fork);
		print_action(philo, FORK);
		pthread_mutex_lock(&cur->next->fork);
		print_action(philo, FORK);
		print_action(philo, EAT);
		usleep(philo->data->eat_time * 1000);
		// cur->ate = 1;
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
		usleep(philo->data->eat_time * 1000);
		// waiter(philo ,philo->data->eat_time);
		// cur->ate = 1;
		pthread_mutex_unlock(&cur->next->fork);
		pthread_mutex_unlock(&cur->fork);
	}
	// waiter(philo, philo->data->eat_time);
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
	usleep(10);
	return (1);
}

void	*routine(void *lophi)
{
	t_philo	*philo;

	philo = (t_philo *)lophi;
	
	if (philo->id % 2 == 0)
		usleep(50);
	// printf("philo is %d\n", philo->id);
	while (1)
	{
		// if (check_dead(philo))
		// 	break;
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
	while (philo)
	{
		tmp = philo->next;
		printf("philo %p %d is washing his plate\n\n\n", philo, philo->id);
		// pthread_mutex_destroy(&(philo->fork));
		ft_lstdelone(philo);
		philo = tmp;
		printf("TEST\n");
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
	// tornado_wipe(&philo);
	return (0);
}
