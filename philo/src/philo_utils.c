/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:04:45 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/29 21:23:43 by tkubanyc         ###   ########.fr       */
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

int	ft_usleep(long time, t_data *data)
{
	long	start;
	long	cur_time;
	long	remain;

	if (get_time(MICROSECONDS) == -1)
		return (0);
	else
	{
		start = get_time(MICROSECONDS);
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

	if (get_value_int(&philo->lock_philo, &philo->is_finish_eating))
		return (0);
	time_cur = get_time(MILLISECONDS) - get_value_long(&philo->lock_philo, &philo->time_last_eat);
	time_die = data->time_die / 1000;
	if (time_cur > time_die)
		return (1);
	return (0);
}

// void cleanup()
// {

// }
