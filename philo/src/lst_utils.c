/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:24:44 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/03 17:09:25 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int id, t_philo *philo)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	if (pthread_mutex_init(&(res->fork), NULL) != 0)
		return (0);
	if (pthread_create(&(res->pid), NULL, routine, philo) != 0)
		return (NULL);
	res->ate = 0;
	res->is_dead = 0;
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

int	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	if (!lst ||!new)
		return (0);
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
	return (1);
}

t_philo	*create_circular(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	while (philo)
		philo = philo->next;
	philo->next = first;
	return (philo);
}

t_philo	*init_chain(t_philo **philo, t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 1;
	while (i <= data->nb_philo)
	{
		if (*philo == NULL)
		{
			*philo = ft_lstnew(i, *philo);
			if (*philo == NULL)
				return (NULL);
		}
		else
		{
			if (!ft_lstadd_back(&tmp, ft_lstnew(i, *philo)))
				return (NULL);
		}
		i++;
	}
	*philo = create_circular(*philo);
	return (*philo);
}
