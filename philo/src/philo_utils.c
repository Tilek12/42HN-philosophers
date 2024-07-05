/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:04:45 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/04 19:16:09 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(t_time_def time_def)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	else
	{
		if (time_def == MICROSECONDS)
			return ((long)(time.tv_sec * 1000000L) + (long)time.tv_usec);
		else if (time_def == MILLISECONDS)
			return ((long)(time.tv_sec * 1000L) + (long)(time.tv_usec / 1000L));
	}
	return (-1);
}

long	cur_time_philo(t_philo *philo)
{
	long	result;

	result = get_time(MILLISECONDS) - get_value_long(&philo->lock_philo,
		&philo->time_last_eat);
	if (result == -1)
		return (0);
	return (result);
}

int	ft_usleep(long time, t_data *data)
{
	long	start;
	long	cur_time;
	long	remain;

	start = get_time(MICROSECONDS);
	if (start == -1)
		return (0);
	else
	{
		while (get_time(MICROSECONDS) - start < time)
		{
			if (is_program_end(data))
				break ;
			cur_time = get_time(MICROSECONDS) - start;
			remain = time - cur_time;
			if (remain > 1000)
				usleep(remain / 2);
			else
				while (get_time(MICROSECONDS) - start < time)
					;
		}
		return (1);
	}
}

int	increase_value(pthread_mutex_t *mutex, int *value)
{
	if (!mutex_handler(mutex, LOCK))
		return (0);
	(*value)++;
	if (!mutex_handler(mutex, UNLOCK))
		return (0);
	return (1);
}

int	threads_ready(pthread_mutex_t *mutex, t_data *data)
{
	int	result;

	result = 0;
	if (!mutex_handler(mutex, LOCK))
		return (-1);
	if (data->threads_counter == data->philo_num)
		result = 1;
	if (!mutex_handler(mutex, UNLOCK))
		return (-1);
	return (result);
}

int	is_philo_dead(t_philo *philo, t_data *data)
{
	long	time_cur;
	long	time_die;
	long	time_last_eat;

	if (get_value_int(&philo->lock_philo, &philo->philo_finish))
		return (0);
	time_cur = get_time(MILLISECONDS) - get_value_long(&philo->lock_philo, &philo->time_last_eat);
	pthread_mutex_lock(&philo->lock_philo);
	time_last_eat = philo->time_last_eat;
	pthread_mutex_unlock(&philo->lock_philo);
	// pthread_mutex_lock(&data->lock_print);
	// printf("philo [%d],  time_last_eat = %ld\n", philo->id_philo, time_last_eat);
	// pthread_mutex_unlock(&data->lock_print);
	// pthread_mutex_lock(&data->lock_print);
	// printf("philo [%d],  time_cur = %ld\n", philo->id_philo, time_cur);
	// pthread_mutex_unlock(&data->lock_print);
	// pthread_mutex_lock(&data->lock_print);
	// printf("philo [%d],  time_cur = %ld\n", philo->id_philo, time_cur);
	// pthread_mutex_unlock(&data->lock_print);
	time_die = (long)(data->time_die / 1000);
	// pthread_mutex_lock(&data->lock_print);
	// printf("philo [%d],  time_die = %ld\n", philo->id_philo, time_die);
	// pthread_mutex_unlock(&data->lock_print);
	if (time_cur >= time_die)
		return (1);
	return (0);
}

int	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (!mutex_handler(&data->philo_array[i].lock_philo, DESTROY))
			return (0);
		i++;
	}
	if (!mutex_handler(&data->lock_data, DESTROY))
		return (0);
	if (!mutex_handler(&data->lock_print, DESTROY))
		return (0);
	free(data->philo_array);
	free(data->fork_array);
	return (1);
}
