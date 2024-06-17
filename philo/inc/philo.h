/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:27 by ramzerk           #+#    #+#             */
/*   Updated: 2024/05/20 21:04:12 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <string.h>      // Pour memset
#include <stdio.h>       // Pour printf
#include <stdlib.h>      // Pour malloc et free
#include <unistd.h>      // Pour write et usleep
#include <sys/time.h>    // Pour gettimeofday
#include <pthread.h>     // Pour pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct s_mutex
{
	pthread_mutex_t mutex;
	
} mutex;


#endif