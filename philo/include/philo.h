/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:48:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/07 19:31:12 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <pthread.h>
# include <sys/time.h>

/*---------------*/
/*  Text colors  */
/*---------------*/
// # define RES "\033[0m"
// # define R "\033[31m"
// # define G "\033[32m"
// # define Y "\033[33m"
// # define B "\033[34m"
// # define M "\033[35m"
// # define C "\033[36m"
// # define W "\033[37m"

typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE,
}			t_action;

typedef enum e_time_def
{
	MICROSECONDS,
	MILLISECONDS,
}			t_time_def;

typedef enum e_option
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_option;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	pthread_t		id_thread;
	int				id_philo;
	t_fork			*fork_1;
	t_fork			*fork_2;
	int				eat_counter;
	pthread_mutex_t	eat_counter_mtx;
	long			time_last_eat;
	pthread_mutex_t	time_last_eat_mtx;
	int				philo_finish;
	pthread_mutex_t	philo_finish_mtx;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	data_mtx;
	pthread_mutex_t	print_mtx;
	pthread_t		watcher;
	t_fork			*fork_array;
	t_philo			*philo_array;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_repeat;
	int				start_ready;
	pthread_mutex_t	start_ready_mtx;
	long			start_time;
	pthread_mutex_t	start_time_mtx;
	int				threads_counter;
	pthread_mutex_t	threads_counter_mtx;
	int				philos_finish;
	pthread_mutex_t	philos_finish_mtx;
	int				end_program;
	pthread_mutex_t	end_program_mtx;
}				t_data;

typedef struct s_thread_data
{
	pthread_mutex_t	td_mtx;
	t_data			*data;
	t_philo			*philos;
	int				i;
}				t_thread_data;

int		input_handler(int argc, char **argv, t_data *data);
int		init_data(int argc, char **argv, t_data *data);
int		init_fork(t_data *data);
int		init_philo(t_data *data);
void	init_philo_forks(t_data *data, int i);
int		ft_atoi(char *str);
int		is_correct_input(char **str);
int		mutex_handler(pthread_mutex_t *mutex, t_option option);
int		thread_handler(pthread_t *thread, void *(*func)(void *),
		void *param, t_option option);
int		error_free(t_data *data);
int		error_free_all(t_data *data, t_thread_data *thread_data);
int		error_malloc(void);
int		get_value_int(pthread_mutex_t *mutex, int *value);
long	get_value_long(pthread_mutex_t *mutex, long *value);
int		set_value_int(pthread_mutex_t *mutex, int *variable, int value);
int		set_value_long(pthread_mutex_t *mutex, long *variable, long value);
int		philo_simulation(t_data *data);
int		create_thread_data(t_thread_data *td, t_data *data);
int		create_threads(t_thread_data *td, t_data *data);
int		join_threads(t_data *data);
int		init_routine_data(t_thread_data *td, t_data **data, t_philo **philo);
void	*routine_general(void *param);
void	*routine_watcher(void *param);
void	*routine_one_philo(void *param);
long	get_time(t_time_def time_def);
long	life_time_philo(t_philo *philo);
long	life_time_program(t_data *data);
int		ft_usleep(long time, t_data *data);
int		increase_value(pthread_mutex_t *mutex, int *value);
int		threads_ready(pthread_mutex_t *mutex, t_data *data);
int		print_action(t_action action, t_philo *philo, t_data *data);
int		eating(t_philo *philo, t_data *data);
int		sleeping(t_philo *philo, t_data *data);
int		thinking(t_philo *philo, t_data *data);
int		over_thinking(t_philo *philo, t_data *data);
int		is_philo_dead(t_philo *philo, t_data *data);
int		is_philo_finish(t_philo *philo, t_data *data);
int		is_all_finish(t_data *data);
int		is_program_end(t_data *data);
int		cleanup(t_data *data, t_thread_data *thread_data);

#endif
