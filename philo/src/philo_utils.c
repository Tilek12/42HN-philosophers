/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:04:45 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/08 16:19:48 by tkubanyc         ###   ########.fr       */
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

long	life_time_philo(t_philo *philo)
{
	return (get_time(MILLISECONDS) - get_value_long(&philo->time_last_eat_mtx, \
		&philo->time_last_eat));
}

long	life_time_program(t_data *data)
{
	return (get_time(MILLISECONDS) - get_value_long(&data->start_time_mtx, \
		&data->start_time));
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
