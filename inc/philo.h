/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 00:07:27 by ramzerk           #+#    #+#             */
/*   Updated: 2024/09/25 21:27:08 by ramzerk          ###   ########.fr       */
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
	pthread_mutex_t	key_mutex;
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
	int				end_philo;
	pthread_mutex_t	all_finished;
	pthread_mutex_t	smn_died;
	int				ac;
	char			**av;
}					t_data;




//############  CHECK_UTILS ##############/

int					check_av(char **av);

int					check_dead(t_philo *philo);

int					check_finished(t_philo *philo);

int 				dead_verif(t_philo *philo);


//############  CLEAN_TOOLS ##############/

int					tornado_wipe(t_philo *philo);

//############  INIT   ##############//

int					init_args(int ac, char **av, t_philo *philo, t_data *data);

t_philo				*init_chain(t_philo *philo, t_data *data);

void				thread_join(t_philo *philo);

//############  LST_UTILS ##############//

int					ft_lstadd_back(t_philo *lst, t_philo *new);

void				create_circular(t_philo *philo);

t_philo				*ft_lstnew(int id, t_data *data);

//############  MINI_LIBFT  #############//

int					ft_isdigit(int c);

int					ft_atoi(char *str);

//############  ROUTINE ##############//

void				*routine(void *lophi);

int					eat(t_philo *philo);

int					sleepy(t_philo *philo);

int					thinky(t_philo *philo);

//############  TIME_TOOLS ##############/

long				time_get(void);

void				waiter(long time);

void				waiter_white(t_philo *philo);

int					print_action(t_philo *philo, char *str);

#endif
