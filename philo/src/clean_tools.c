/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:09:43 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/18 15:39:19 by rabouzia         ###   ########.fr       */
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

	printf("wipey\n");
	first = philo;
	philo = philo->next;
	while (philo)
	{
		tmp = philo->next;
		printf("philo %d is washing his plate\n\n\n", philo->id);
		pthread_mutex_destroy(&philo->fork);
		ft_lstdelone(philo);
		philo = tmp;
		if (philo == first)
			break ;
	}
}
