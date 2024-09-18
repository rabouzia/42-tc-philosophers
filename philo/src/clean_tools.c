/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:09:43 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/18 17:33:19 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	first = philo;
	philo = philo->next;
	while (philo)
	{
		tmp = philo->next;
		pthread_mutex_destroy(&philo->fork);
		ft_lstdelone(philo);
		philo = tmp;
		if (philo == first)
			break ;
	}
}
