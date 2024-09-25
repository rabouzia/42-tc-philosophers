/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:11 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 23:03:33 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_first(t_philo *philo, t_data *data)
{
	if (pthread_mutex_init(&(philo->fork), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(philo->key_mutex), NULL) != 0)
		return (0);
	philo->data = data;
	philo->ate = 0;
	philo->id = 1;
	philo->last_eat = time_get();
	philo->next = NULL;
	if (philo->data->ac == 6)
		philo->nb_meals = ft_atoi(data->av[4]);
	return (1);
}

t_philo	*init_chain(t_philo *philo, t_data *data)
{
	int	i;

	if (!init_first(philo, data))
		return (NULL);
	i = 2;
	while (i <= data->nb_philo)
	{
		if (!ft_lstadd_back(philo, ft_lstnew(i, data)))
			return (NULL);
		i++;
	}
	create_circular(philo);
	return (philo);
}

t_data	*init_philo(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[0]);
	data->life_range = ft_atoi(av[1]);
	data->eat_time = ft_atoi(av[2]);
	data->sleep_time = ft_atoi(av[3]);
	data->is_dead = 0;
	data->start_time = time_get();
	data->end_philo = 0;
	data->ac = ac;
	data->av = av;
	return (data);
}

int	init_args(int ac, char **av, t_philo *philo, t_data *data)
{
	t_philo	*tmp;

	data = init_philo(ac, av, data);
	philo = init_chain(philo, data);
	tmp = philo;
	while (tmp)
	{
		if (pthread_create(&(tmp->pid), NULL, routine, tmp) == -1)
			return (tornado_wipe(philo), 0);
		tmp = tmp->next;
		if (tmp == philo)
			break ;
	}
	return (1);
}

int	thread_join(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		if (pthread_join(tmp->pid, NULL) != 0)
			return (0);
		tmp = tmp->next;
		if (tmp == philo)
			break ;
	}
	return (1);
}
