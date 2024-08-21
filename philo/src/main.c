/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/08/19 01:53:42 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long time_get(void)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL)== -1)
		return 0;
	return ((tv.tv_sec * 1000) + (tv.tv_sec / 1000));
}

	// t_philo *philo;
	// philo = (t_philo *) lophi;
	// while(!philo->is_dead)
	// {
	// 	pthread_mutex_lock(&(philo->fork));
	// 	eat()
	// 	pthread_mutex_unlock(&(philo->fork));	
	// }
	// mutex -> fork
	// take 2 forks  (take always phlio->next fork)-> lock 2 mutex
	// mange time_to_eat
	// pose les fork -> mutex unlock the 2
	// sleep time to sleep
	// else think
	// return philo;
int eat(t_philo *philo)
{
	t_philo *cur;
	cur = philo;
	pthread_mutex_lock(&cur->fork);
	if (cur->next == NULL)
		pthread_mutex_lock(&philo->fork);
	else 
		pthread_mutex_lock(&cur->next->fork);
	usleep(philo->data->eat_time);
	cur->ate = 1;
	pthread_mutex_unlock(&cur->fork);
	if (cur->next == NULL)
		pthread_mutex_unlock(&philo->fork);
	else 
		pthread_mutex_unlock(&cur->next->fork);
	
	return 1;
}
int think(void)//t_philo *philo)
{
	
		
}
int sleepy(void)//t_philo *philo)
{
	
}

int try_eat(void)
{
	tous essaie de manger, commence par le premier, et les timer commences
}

void *routine(void *lophi)
{
	t_philo *philo;
	philo = (t_philo *) lophi;
	while(1)
	{
		if(!eat(philo))
			break;
		if(!sleepy())
			break;
		if(!think())
			break;
	}

}
int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	bzero(&data, sizeof(t_data));
	if (!(ac == 5 || ac == 6))
		return (write(2, "Error\nWrong number of arguments\n", 32),0);
	if (!check_av(av + 1))
			return (0);
	init_args(ac, av + 1, &philo, &data);
	printf("time get :%li\n", time_get());
		// print_philo(&philo);
	return (0);
}

/*
av
[1]		number_of_philo
[2]		time_to_die
[3] 	time_to_eat
[4] 	time_to_sleep
[5]		number_of_times_each_philosophers_must_eat

// if (ac == 5 || ac == 6)
// {
//     if(!check_av(av))
//         return (0);
// }


	TODO each philo is thread
	TODO There is one fork between each pair of philosophers. Therefore,
		if there are several
	philosophers,
		each philosopher has a fork on their left side and a fork on their right
	side. If there is only one philosopher,
		there should be only one fork on the table.
	TODO To prevent philosophers from duplicating forks,
		you should protect the forks state
	with a mutex for each of them.


philo1 -> philo2 -> philo3 -> philo1

init
lance
routine :
	take fork
		-> left fork or right fork    left fork => philo->fork :: right fork => philo->next->fork mutex_lock(left_fork)
	take fork 2 -> right fork or left fork mutex_lock(right_fork)
	eat
	give back forks
	sleep
*/