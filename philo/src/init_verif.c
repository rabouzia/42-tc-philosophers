/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:31:11 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/23 13:28:50 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_goodvalue(char **av)
{
	if (ft_atoi(av[0]) < 1 || ft_atoi(av[0]) > 200)
		return 0;
	if (ft_atoi(av[1]) < 60 || ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60)
		return 0;
	return 1;
}

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
	if (!is_goodvalue(av))
		return (0);
	return (1);
}

t_data	*init_philo(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[0]);
	data->life_range = ft_atoi(av[1]);
	data->eat_time = ft_atoi(av[2]);
	data->sleep_time = ft_atoi(av[3]);
	data->is_dead = 0;
	data->start_time = time_get();
	return (data);
	data->ac = ac;
	data->av = av;
}

int	init_args(int ac, char **av, t_philo *philo, t_data *data)
{
	t_philo	*tmp;

	data = init_philo(ac, av, data);
	philo = init_chain(philo, data);
	tmp = philo;
	while (tmp)
	{
		pthread_create(&(tmp->pid), NULL, routine, tmp);
		tmp = tmp->next;
		if (tmp == philo)
			break ;
	}
	// printf("arg 4 is %d\n" ,ft_atoi(av[4]));

	return (1);
}
