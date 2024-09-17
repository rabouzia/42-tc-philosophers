/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:24:44 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/17 23:17:22 by rabouzia         ###   ########.fr       */
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
	res->ate = 0;
	res->last_eat = time_get();
	res->id = id;
	res->next = NULL;
	return (res);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_philo	*ft_lstfirst(t_philo *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstadd_back(t_philo *lst, t_philo *new)
{
	if (!lst ||!new)
		return (0);
	ft_lstlast(lst)->next = new;
	return (1);
}

void	create_circular(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = first;
}

int init_first(t_philo *philo, t_data *data)
{
	pthread_mutex_init(&(philo->fork), NULL);
	philo->data = data;
	philo->ate = 0;
	philo->id = 1;
	philo->last_eat = time_get();	
	philo->next = NULL;
	return (0);
}

t_philo	*init_chain(t_philo *philo, t_data *data)
{
	int		i;

	init_first(philo, data);
	i = 2;
	while (i <= data->nb_philo)
	{
		if (!ft_lstadd_back(philo, ft_lstnew(i, data)))
			return (/*free les philos d'avant, */NULL);
		i++;
	}
	create_circular(philo);
	return (philo);
}