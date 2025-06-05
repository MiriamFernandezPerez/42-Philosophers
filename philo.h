/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:57:14 by marvin            #+#    #+#             */
/*   Updated: 2022/06/17 14:06:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

# define ERR_MALL "Malloc error, please check your computer's memory\n"
# define ERR_ARGS "Wrong arguments quantity, this program require:\n"
# define NUM_PH "1-Number of philosophers\n"
# define TIMES "2-Time to die\n3-Time to eat\n4-Time to sleep\n"
# define OPTIONAL "5-Number of times each philosopher must eat (Optional)\n"
# define NEG "Negative values are not allowed\n"
# define MAX "Number too big, can't be higher than MAX_INT\n"
# define NOT_DIG "Error. Not a digit value\n"
# define ZERO "Number Zero not allowed\n"
# define NO_TIME "Use more than 60ms\n"
# define TH_CODE "Wrong Thread Code\n"
# define MUT_CODE "Wrong Mutex Code\n"
# define VALUE_MUTEX "The value specified by mutex is invalid\n"
# define VALUE_ATTR "The value specified by attr is invalid\n"
# define DEAD "A deadlock would occur is the thread blocked waiting for mutex\n"
# define PERM "The current thread does nor hold a lock on mutex.\n"
# define NO_MEM "Process can't allocate enough memory to create another mutex\n"
# define BUSY "Mutex is locked\n"
# define AGAIN "No resources to create another thread\n"
# define NO_PERM "The caller does not have appropiate permission\n"
# define NO_JOIN "The value speccified by thread is not joinable\n"
# define SRCH "No thread could be found by the given thread ID, thread.\n"
# define DEADLK "Deadlock detected or calue of thread specifies the thread\n"

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}			t_code;

typedef enum e_event_id
{
	DEATH,
	EAT,
	THINK,
	SLEEP,
	FORK,
	DROP,
}		t_event_id;

typedef struct s_philo
{
	int				id;
	int				num_eats;
	long			last_eat;
	int				fork_r;
	int				fork_l;
	pthread_mutex_t	num_eats_mutex;
	pthread_mutex_t	mutex_last_eat;
}	t_philo;

typedef struct s_data
{
	int				init_philo;
	int				stat;
	int				id;
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_meals;
	bool			init;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	init_philo_mutex;
	pthread_mutex_t	mutex_stat;
	pthread_mutex_t	mutex_id;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_fork;
	long			s_time;
}	t_data;

/*philo.c*/
int		ft_msn(char *s, int fd);
int		ft_error(char *error_msg);
int		ft_malloc(t_data *data);
int		main(int ac, char **av);

/*utils.c*/
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		check_limits(long int n);
int		ft_isdigit(char c);
int		ft_isspace(char c);

/*check_arg.c*/
char	*check_input(char *str);
long	ft_atol(char *str);
int		check_digits(char *s);
int		check_arg(char **av, int ac);

/*time_utils.c*/
void	w_status(char *s, t_data *d, int i);
long	current_time(void);
void	wait_usleep(int time);

/*handle_mutex.c*/
int		create_mutex(t_data *d);
int		mutex_error(int status, t_code code);
int		handle_mutex(pthread_mutex_t *mutex, t_code code);

/*handle_thread.c*/
int		create_thread(t_data *d);
int		thread_error(int status, t_code code);
int		handle_thread(pthread_t *th, void *(*f)(void *), void *data, t_code c);

/*init.c*/
int		init_philos(t_data *d);
int		init_data(t_data *d);
void	wait_threads(t_data *d);
int		start_simulation(t_data *d);
int		init(t_data *data, int ac, char **av);

/*routine.c*/
int		check_status(t_data *d);
int		philo_routine(t_data *d);
void	*routine(void *f);

/*actions.c*/
void	take_fork(t_data *d, int i);
void	philo_eat(t_data *d, int i);
void	philo_sleep(t_data *d, int i);

/*monitor.c*/
int		check_nbr_meals(t_data *d, int i, int count);
int		check_eats(t_data *d, int i, int count);
void	ft_print_die(long t, int i);
int		check_last_eat(t_data *d, int i, long time);
int		monitor(t_data *d);

/*ft_free.c*/
void	ft_free(t_data *d);

#endif
