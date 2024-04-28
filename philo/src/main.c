/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:15 by ramzerk           #+#    #+#             */
/*   Updated: 2024/04/27 08:15:20 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int is_alpha(char c)
// {
// 	if (c >= '0' && c <= '9')
// 		return 1;
// 	return 0;
// }

// int	is_valid(char *str)
// {
// 	int	(i) = 0;
// 	while(str[i])
// 	{
// 		if(!(is_alpha(str[i])))
// 			return 0;
// 		i++;
// 	}
// 	return (1);
// }

// int valid_arg(char **av)
// {
// 	int(i) = 0;
// 	while (*av)
// 	{
// 		if (!is_valid(av))
// 			return 0;
// 		av++;
// 	}
// 	return 1;
// }


// int main (int ac, char **av)
// {
// 	if (ac != 5 || ac != 6)
// 		return 0;
// 	if (!valid_arg(av + 1))
// 		return 0;	
// }

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
  
pthread_t tid[2]; 
int counter; 
  
void* trythis(void* arg) 
{ 
    unsigned long i = 0; 
    counter += 1; 
    printf("\n Job %d has started\n", counter); 
  
    for (i = 0; i < (0xFFFFFFFF); i++) 
        ; 
    printf("\n Job %d has finished\n", counter); 
  
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
  
    while (i < 2) { 
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
        if (error != 0) 
            printf("\nThread can't be created : [%s]", strerror(error)); 
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
  
    return 0; 
} 

/*
	TODO each philo is thread
	TODO There is one fork between each pair of philosophers. Therefore, if there are several
	philosophers, each philosopher has a fork on their left side and a fork on their right
	side. If there is only one philosopher, there should be only one fork on the table.
	TODO To prevent philosophers from duplicating forks, you should protect the forks state
	with a mutex for each of them.

*/