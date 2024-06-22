/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:48:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/22 15:34:56 by tkubanyc         ###   ########.fr       */
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
	int			id_philo;
	pthread_t	id_thread;
	t_fork		*fork_1;
	t_fork		*fork_2;
	int			eat_counter;
	int			last_eating;
	int			finish;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	*block;
	t_fork			*fork_array;
	t_philo			*philo_array;
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eat_repeat;
	int				philos_ready;
	int				start_time;
	int				end;
}				t_data;

int		input_handler(int argc, char **argv, t_data *data);
int		init_data(int argc, char **argv, t_data *data);
int		init_fork(t_data *data);
void	init_philo(t_data *data);
void	init_philo_forks(t_data *data, int i);
int		ft_atoi(char *str);
int		is_correct_input(char **str);
int		mutex_handler(pthread_mutex_t *mutex, t_option option);
int		thread_handler(pthread_t *thread, void *(*func)(void *),
		void *info, t_option option);
int		error_free(t_data *data);
int		error_malloc(void);
int		get_value(pthread_mutex_t *mutex, int *value, t_data *data);
int		set_value(pthread_mutex_t *mutex, int *variable,
		int value, t_data *data);
int		is_finished(t_data *data);

#endif
