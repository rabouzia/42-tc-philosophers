/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:09:43 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/20 15:41:41 by rabouzia         ###   ########.fr       */
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
		pthread_mutex_destroy(&philo->fork);
		printf("philo number %d \n", philo->id);
		free(philo);
		philo = tmp;
		if (philo == first)
			break ;
	}
	return (1);
}
