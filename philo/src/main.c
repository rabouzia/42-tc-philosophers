/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/18 17:50:51 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *lophi)
{
	t_philo	*philo;

	philo = (t_philo *)lophi;
	if (philo->id % 2 == 0)
		waiter(1);
	while (1)
	{
		if (philo->data->ac == 6)
		{
			if (!check_finished(philo))
				break ;
		}
		if (!check_dead(philo))
			break ;
		if (!eat(philo))
			break ;
		if (!sleepy(philo))
			break ;
		if (!thinky(philo))
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;

	bzero(&data, sizeof(t_data));
	bzero(&philo, sizeof(t_philo));
	if (!(ac == 5 || ac == 6))
		return (write(2, "Error\nWrong number of arguments\n", 32), 0);
	if (!check_av(av + 1))
		return (0);
	// while (1)
	// {
	// 	if (monitoring())
	// 		break;
	// }
	init_args(ac, av + 1, &philo, &data);
	tornado_wipe(&philo);
	return (0);
}
