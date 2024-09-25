/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:24:44 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 21:08:23 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int id, t_data *data)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->data = data;
	pthread_mutex_init(&(res->fork), NULL);
	pthread_mutex_init(&(res->key_mutex), NULL);
	res->ate = 0;
	res->last_eat = time_get();
	res->id = id;
	res->next = NULL;
	if (res->data->ac == 6)
		res->nb_meals = ft_atoi(data->av[4]);
	return (res);
}

void	create_circular(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = first;
}