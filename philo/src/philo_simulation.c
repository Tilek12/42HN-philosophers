/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/07 19:32:36 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	cleanup(t_data *data, t_thread_data *thread_data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (!mutex_handler(&data->philo_array[i].time_last_eat_mtx, DESTROY)
			|| !mutex_handler(&data->philo_array[i].philo_finish_mtx, DESTROY)
			|| !mutex_handler(&data->philo_array[i].eat_counter_mtx, DESTROY))
			return (0);
		i++;
	}
	if (!mutex_handler(&data->data_mtx, DESTROY)
		|| !mutex_handler(&data->print_mtx, DESTROY)
		|| !mutex_handler(&data->start_ready_mtx, DESTROY)
		|| !mutex_handler(&data->start_time_mtx, DESTROY)
		|| !mutex_handler(&data->threads_counter_mtx, DESTROY)
		|| !mutex_handler(&data->philos_finish_mtx, DESTROY)
		|| !mutex_handler(&data->end_program_mtx, DESTROY))
		return (0);
	if (data->philo_array != NULL)
		free(data->philo_array);
	if (data->fork_array != NULL)
		free(data->fork_array);
	if (thread_data != NULL)
		free(thread_data);
	return (1);
}

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

int	create_threads(t_thread_data *td, t_data *data)
{
	int	i;
	int	philo_num;

	i = 0;
	philo_num = data->philo_num;
	while (i < philo_num)
	{
		if (!set_value_int(&td->td_mtx, &td->i, i))
			return (0);
		if (!thread_handler(&td->philos[i].id_thread,
			routine_general, td, CREATE))
			return (0);
		i++;
		usleep(50);
	}
	return (1);
}

int	create_thread_data(t_thread_data *td, t_data *data)
{
	if (!mutex_handler(&data->data_mtx, LOCK))
		return (0);
	td->data = data;
	td->philos = data->philo_array;
	if (!mutex_handler(&data->data_mtx, UNLOCK))
		return (0);
	if (!mutex_handler(&td->td_mtx, INIT))
		return (0);
	return (1);
}

int	philo_simulation(t_data *data)
{
	t_thread_data	*td;

	td = NULL;
	if (data->eat_repeat == 0 || data->philo_num == 0)
	{
		if (!cleanup(data, td))
			return (error_free_all(data, td));
		return (1);
	}
	else if (data->philo_num == 1)
	{
		if (!thread_handler(&data->philo_array[0].id_thread,
				routine_one_philo, data, CREATE))
			return (error_free(data));
	}
	else
	{
		td = (t_thread_data *)malloc(sizeof(t_thread_data));
		if (td == NULL || !create_thread_data(td, data))
			return (error_free(data));
		if (!create_threads(td, data))
			error_free_all(data, td);
	}
	if (!thread_handler(&data->watcher, routine_watcher, data, CREATE))
		return (error_free_all(data, td));
	if (!set_value_long(&data->start_time_mtx, &data->start_time,
			get_time(MILLISECONDS))
		|| !set_value_int(&data->start_ready_mtx, &data->start_ready, 1))
		return (error_free_all(data, td));
	mutex_handler(&data->print_mtx, LOCK);
	printf("--- start_time = %ld ---\n", data->start_time);
	mutex_handler(&data->print_mtx, UNLOCK);
	if (!join_threads(data)
		|| !set_value_int(&data->end_program_mtx, &data->end_program, 1))
		return (error_free_all(data, td));
	if (!cleanup(data, td))
		return (error_free_all(data, td));
	printf("--- Program is finished! ---\n");
	return (1);
}
