/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:48:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/26 20:58:50 by tkubanyc         ###   ########.fr       */
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
# define RES "\033[0m"
# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define M "\033[35m"
# define C "\033[36m"
# define W "\033[37m"

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
	pthread_mutex_t	lock_philo;
	pthread_t		id_thread;
	int				id_philo;
	t_fork			*fork_1;
	t_fork			*fork_2;
	int				eat_counter;
	int				last_eating;
	int				is_finish_eating;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	lock_data;
	pthread_mutex_t	lock_print;
	t_fork			*fork_array;
	t_philo			*philo_array;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_repeat;
	int				start_ready;
	int				start_time;
	int				end_program;
}				t_data;

typedef struct s_thread_data
{
	t_data	*data;
	t_philo	*philo;
	int		error_eat;
	int		error_sleep;
	int		error_think;
	int		error_get_value;
	int		error_is_program_end;
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
int		error_malloc(void);
int		get_value(pthread_mutex_t *mutex, int *value);
int		set_value(pthread_mutex_t *mutex, int *variable, int value);
int		is_program_end(t_data *data);
int		philo_start(t_data *data);
void	*philo_run(void *param);
// int		philo_run(t_philo *philo, t_data *data);
int		get_time(t_time_def time_def);
int		ft_usleep(int time, t_data *data);
int		print_action(t_action action, t_philo *philo, t_data *data);
int		eating(t_philo *philo, t_data *data);
int		sleeping(t_philo *philo, t_data *data);
int		thinking(t_philo *philo, t_data *data);

#endif
