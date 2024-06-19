/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:48:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/19 09:28:52 by tkubanyc         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	int			id_philo;
	pthread_t	id_thread;
	t_fork		fork_left;
	t_fork		fork_right;
	int			eat_counter;
	int			last_eating;
	int			finish;
	t_data		*data;
}				t_philo;

struct s_data
{
	t_fork	*fork_array;
	t_philo	*philo_array;
	int		philo_num;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eat_repeat;
	int		start_time;
	int		end;
};

int		input_handler(int argc, char **argv, t_data *data);
int		ft_atoi(char *str);
int		is_correct_input(char **str);
int		init_mutex(pthread_mutex_t *mutex, t_option option);
int		init_thread(pthread_t *thread, void *(*func)(void *),
	void *info, t_option option);

#endif
