/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:11 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/17 17:41:11 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_av(char **av)
{
	short	i;
	short	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_data	*init_philo(int ac, char **av, t_data *data)
{
	data->nb_philo   = ft_atoi(av[0]);   // number_of_philosophers:
	data->life_range = ft_atoi(av[1]); // time_to_die
	data->eat_time   = ft_atoi(av[2]);   // time_to_eat
	data->sleep_time = ft_atoi(av[3]); // time_to_sleep
	data->is_dead = 0;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[4]);
	data->start_time = time_get();
		return (data);
}

void	print_philo(t_philo *a)
{
	printf("show id :\n");
	while (a)
	{
		// id_print(a);
		printf("id = %d and ptr = %p\n", a->id, a);
		a = a->next;
	}
}

void	init_args(int ac, char **av, t_philo *philo, t_data *data)
{
	data = init_philo(ac, av, data);
	philo = malloc(sizeof(t_philo));
	philo = init_chain(philo, data);
	t_philo *tmp = philo;
	while (tmp)
	{
		pthread_create(&(tmp->pid), NULL, routine, tmp);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}
	tmp = philo;
	while (tmp)
	{
		pthread_join(tmp->pid,NULL);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}	
}