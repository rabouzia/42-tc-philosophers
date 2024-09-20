/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:27 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/20 13:54:10 by rabouzia         ###   ########.fr       */
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

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	long			last_eat;
	pthread_t		pid;
	int				nb_meals;
	struct s_philo	*next;
	pthread_mutex_t	fork;
	struct s_data	*data;

}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	long			life_range;
	long			eat_time;
	long			sleep_time;
	long			start_time;
	int				is_dead;
	int				end;
	pthread_mutex_t	all_finished;
	pthread_mutex_t	smn_died;
	int				ac;
	char			**av;
}					t_data;

void *routine(void *lophi);

//############  INIT_VERIF   ##############//

int					check_av(char **av);

int				init_args(int ac, char **av, t_philo *philo, t_data *data);

//############  MINI_LIBFT  #############//

int					ft_isdigit(int c);

int					ft_atoi(char *str);

int					ft_lstadd_back(t_philo *lst, t_philo *new);

//############  PHILO_UTILS ##############//

int					check_dead(t_philo *philo);

long				time_get(void);

int 				check_finished(t_philo *philo);

void				waiter(long time);

int					print_action(t_philo *philo, char *str);

//############  ROUTINE ##############//

int					eat(t_philo *philo);

int					sleepy(t_philo *philo);

int					thinky(t_philo *philo);

//############  CLEAN_TOOLS ##############/

int				tornado_wipe(t_philo *philo);

//############  CREATE_LST ##############/

t_philo				*init_chain(t_philo *philo, t_data *data);

#endif
