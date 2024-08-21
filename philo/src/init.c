/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:11 by ramzerk           #+#    #+#             */
/*   Updated: 2024/08/17 16:48:21 by ramzerk          ###   ########.fr       */
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
	if (ac == 6)
		data->nb_meals = ft_atoi(av[4]);
	// if(!pthread_mutex_init(&(data->die), NULL))
	// 	return (NULL);
	// if(!pthread_mutex_init(&(data->eat), NULL))
	// 	return (NULL);
	// if(!pthread_mutex_init(&(data->think), NULL))
	// 	return (NULL);
	return (data);
}

void lay_the_table(t_philo *philo)
{
	pthread_t pd_t;
	int i = 0;
	while(i <= philo->data->nb_philo)
	{
		pthread_mutex_init(&(philo->fork), NULL);
		philo = philo->next;
		i++;
	}
	pthread_create(&pd_t, NULL, routine, NULL);
	pthread_join(pd_t, NULL);
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

void	init_args(int ac, char **av, t_philo **philo, t_data *data)
{
	data = init_philo(ac, av, data);
	philo = init_chain(philo, data);
	// print_philo(philo);
}