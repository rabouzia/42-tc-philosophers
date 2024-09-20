/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:09:43 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/20 16:39:09 by rabouzia         ###   ########.fr       */
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

int	tornado_wipe(t_philo *philo)
{
	t_philo	*first;
	t_philo	*tmp;

	first = philo;
	philo = philo->next;
	while (philo)
	{
		tmp = philo->next;
		if (philo == first)
			break ;
		pthread_mutex_destroy(&philo->fork);
		printf("philo number %d \n", philo->id);
		free(philo);
		philo = tmp;
	}
	return (1);
}
