/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 16:55:07 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*----------------------------*/
/*  Join all created threads  */
/*----------------------------*/
int	join_threads(t_data *data)
{
	int	i;
	int	philo_num;

	i = 0;
	philo_num = data->philo_num;
	while (i < philo_num)
	{
		if (!thread_handler(&data->philo_array[i].id_thread, NULL, NULL, JOIN))
			return (0);
		i++;
	}
	if (!thread_handler(&data->watcher, NULL, NULL, JOIN))
		return (0);
	return (1);
}

/*--------------------------------------------------------------*/
/*  Set the start_time of the simulation that equals to         */
/*  time_last_eat of each philo at the start of the simulation  */
/*--------------------------------------------------------------*/
int	set_start_time(t_data *data)
{
	long	start_time;
	int		i;

	start_time = get_time(MILLISECONDS);
	if (start_time == -1)
		return (0);
	if (!set_value_long(&data->start_time_mtx, &data->start_time, start_time))
		return (0);
	i = 0;
	while (i < data->philo_num)
	{
		if (!set_value_long(&data->philo_array[i].time_last_eat_mtx, \
			&data->philo_array[i].time_last_eat, start_time))
			return (0);
		i++;
	}
	if (!set_value_int(&data->start_ready_mtx, &data->start_ready, 1))
		return (0);
	return (1);
}

/*---------------------------------------------*/
/*  Create threads with thread_data structure  */
/*---------------------------------------------*/
int	create_threads(t_data *data, t_thread_data **td)
{
	int	i;

	*td = (t_thread_data *)malloc(sizeof(t_thread_data));
	if (*td == NULL)
		return (error_malloc());
	if (!mutex_handler(&data->data_mtx, LOCK))
		return (0);
	(*td)->data = data;
	(*td)->philos = data->philo_array;
	if (!mutex_handler(&data->data_mtx, UNLOCK))
		return (0);
	if (!mutex_handler(&(*td)->td_mtx, INIT))
		return (0);
	i = 0;
	while (i < data->philo_num)
	{
		if (!set_value_int(&(*td)->td_mtx, &(*td)->i, i))
			return (0);
		if (!thread_handler(&(*td)->philos[i].id_thread, routine_philo, \
			*td, CREATE))
			return (0);
		i++;
		usleep(500);
	}
	return (1);
}

/*---------------------------------------*/
/*  Start the simulation of the program  */
/*---------------------------------------*/
int	philo_simulation(t_data *data)
{
	int				result;
	t_thread_data	*td;

	td = NULL;
	if (data->philo_num == 1)
	{
		if (!thread_handler(&data->philo_array[0].id_thread, \
			routine_one_philo, data, CREATE))
			return (error_free(data));
	}
	else
	{
		if (!create_threads(data, &td))
			return (error_free_all(data, td));
	}
	if (!thread_handler(&data->watcher, routine_watcher, data, CREATE)
		|| !set_start_time(data)
		|| !join_threads(data)
		|| !set_value_int(&data->finish_mtx, &data->finish, 1))
		return (error_free_all(data, td));
	result = error_check(data);
	if (!cleanup(data, td))
		return (error_free_all(data, td));
	return (result);
}
