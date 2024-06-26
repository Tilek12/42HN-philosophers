/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/26 21:24:26 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_time(t_time_def time_def)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	if (time_def == MICROSECONDS)
		return ((time.tv_sec * 1000000) + (int)time.tv_usec);
	else if (time_def == MILLISECONDS)
		return ((time.tv_sec * 1000) + (int)(time.tv_usec / 1000));
	else
		return (-1);
}

int	ft_usleep(int time, t_data *data)
{
	int	start;
	int	cur_time;
	int	remain;

	if (get_time(MICROSECONDS) == -1)
		return (0);
	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < time)
	{
		if (is_program_end(data))
			break;
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

// void	*philo_run(void *param)
// {
// 	t_data	*data;

// 	data = (t_data *)param;
// 	while (get_value(&data->block_data, &data->start_ready))
// 		;
// 	while (!is_program_end(data))
// 	{
// 		if ()
// 	}
// 	return (NULL);
// }


void	*philo_run(void *param)
{
	t_thread_data	*td;

	td = (t_thread_data *)param;
	if (get_value(&td->data->lock_data, &td->data->start_ready) == -1)
	{
		td->error_get_value = 1;
		printf(Y"---Error! philo_run -> get_value---\n"RES);
	}
	else
	{
		td->error_get_value = 0;
		while (get_value(&td->data->lock_data, &td->data->start_ready) != 1)
			;
	}
	if (is_program_end(td->data) == -1)
	{
		td->error_is_program_end = 1;
		printf(G"---Error! philo_run -> is_program_end---\n"RES);
	}
	else
	{
		td->error_is_program_end = 0;
		while (is_program_end(td->data) != 1)
		{
			if (td->philo->is_finish_eating)
				break ;
			if (!eating(td->philo, td->data))
				td->error_eat = 1;
			else
				td->error_eat = 0;
			if (!sleeping(td->philo, td->data))
				td->error_sleep = 1;
			else
				td->error_sleep = 0;
			if (!thinking(td->philo, td->data))
				td->error_think = 1;
			else
				td->error_think = 0;
		}
	}
	return (NULL);
}

int	philo_start(t_data *data)
{
	int	i;
	t_thread_data *td;

	td = malloc(sizeof(t_thread_data));
	if (data->eat_repeat == 0)
		return (1);
	else if (data->philo_num == 1)
		;
	else
	{
		i = 0;
		while (i < data->philo_num)
		{
			td->data = data;
			td->philo = &data->philo_array[i];
			if (!thread_handler(&data->philo_array[i].id_thread, philo_run, &td, CREATE)
				|| td->error_eat || td->error_sleep || td->error_think
				|| td->error_get_value || td->error_is_program_end)
				return (free(td), error_free(data));
			ft_usleep(10, data);
			i++;
		}
	}
	if (get_time(MILLISECONDS) == -1)
		(error_free(data));
	else
		data->start_time = get_time(MILLISECONDS);
	if (!set_value(&data->lock_data, &data->start_ready, 1))
		return (error_free(data));
	printf(R"error\n"RES);
	printf("is_program_end = %d\n", is_program_end(data));
	i = 0;
	while (i < data->philo_num)
	{
		if (!thread_handler(&data->philo_array[i].id_thread, NULL, NULL, JOIN))
			return (free(td), error_free(data));
		i++;
	}
	free(td);
	td = NULL;
	return (1);
}

// void cleanup()
// {

// }
