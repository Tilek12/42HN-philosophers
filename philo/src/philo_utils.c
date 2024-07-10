/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:04:45 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 17:09:40 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*------------------------*/
/*  Get the current time  */
/*------------------------*/
long	get_time(t_time_def time_def)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (error("Invalid return of gettimeofday() function"));
	else
	{
		if (time_def == MICROSECONDS)
			return ((long)(time.tv_sec * 1000000L) + (long)time.tv_usec);
		else if (time_def == MILLISECONDS)
			return ((long)(time.tv_sec * 1000L) + (long)(time.tv_usec / 1000L));
	}
	return (error("Invalid return of get_time() function"));
}

/*--------------------------------------------------------------------------*/
/*  Calculate the life time of certain philo relative to the time_last_eat  */
/*--------------------------------------------------------------------------*/
long	life_time_philo(t_philo *philo)
{
	return (get_time(MILLISECONDS) - get_value_long(&philo->time_last_eat_mtx, \
		&philo->time_last_eat));
}

/*--------------------------------------------------------------------*/
/*  Calculate the life time of simulation relative to the start_time  */
/*--------------------------------------------------------------------*/
long	life_time_program(t_data *data)
{
	return (get_time(MILLISECONDS) - get_value_long(&data->start_time_mtx, \
		&data->start_time));
}

/*----------------------------*/
/*  Precised usleep function  */
/*----------------------------*/
int	ft_usleep(long sleep_time, t_data *data)
{
	long	start;
	long	life_time;
	long	remain;

	start = get_time(MICROSECONDS);
	if (start == -1)
		return (0);
	else
	{
		while (get_time(MICROSECONDS) - start < sleep_time)
		{
			if (is_program_end(data))
				break ;
			life_time = get_time(MICROSECONDS) - start;
			remain = sleep_time - life_time;
			if (remain > 1000)
				usleep(remain / 2);
			else
				while (get_time(MICROSECONDS) - start < sleep_time)
					;
		}
		return (1);
	}
}

/*------------------------------------*/
/*  Check if all threads are created  */
/*------------------------------------*/
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
