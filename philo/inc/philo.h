/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:27 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/06 17:35:54 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FIRST 1
# define SECOND 2
# define FORK "has taken a fork"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "died"

struct s_data;

typedef struct s_philo
{
	int				id;
	int 			ate;
	int 			is_dead;
	pthread_t		pid;
	struct s_philo	*next;
	pthread_mutex_t	fork;
	struct s_data	*data;

}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	long		life_range;
	long		eat_time;
	long		sleep_time;
	long		start_time;
	int				nb_meals;
	// pthread_mutex_t eat;
	// pthread_mutex_t die;
	// pthread_mutex_t think;
}					t_data;

//########### INIT & CHECK ########/

int					check_av(char **av);
void				init_args(int ac, char **av, t_philo *philo, t_data *data);
void 				*routine(void *lophi);
t_philo				*init_chain(t_philo *philo, t_data *data);
long 				time_get(void);
void 				print_timestamp(t_philo *philo, t_data * data);
long 				time_get(void);

//############# LIBFT #############/

int					ft_isdigit(int c);
int					ft_atoi(char *str);

//############# Test ##############/

void				print_philo(t_philo *a);

#endif
