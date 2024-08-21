/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:24:44 by ramzerk           #+#    #+#             */
/*   Updated: 2024/08/18 21:44:26 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int id, t_philo *philo)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->id = id;
	if(!pthread_create(res, NULL, routine, philo))
		return NULL;
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
	if (!lst || !new)
		return 0;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
	return 1;
}

t_philo	*init_chain(t_philo **philo, t_data *data)
{
	int		i;
	t_philo	*tmp;
	int		tmp_int;
	
	i = 1;
	while (i <= data->nb_philo)
	{
		if (*philo == NULL)
		{
			*philo = ft_lstnew(i, *philo);
			if(*philo == NULL)
				return NULL;
		}
		else
		{
			if(!ft_lstadd_back(&tmp, ft_lstnew(i, *philo)))
				return NULL;
		}
		i++;
	}
	return (*philo);
}
