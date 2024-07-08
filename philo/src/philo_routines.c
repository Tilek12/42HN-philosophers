/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:48:57 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/08 16:18:46 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_routine_data(t_thread_data *td, t_data **data, t_philo **philo)
{
	if (!mutex_handler(&td->data->data_mtx, LOCK))
		return (0);
	*data = td->data;
	if (!mutex_handler(&td->data->data_mtx, UNLOCK))
		return (0);
	if (!mutex_handler(&td->td_mtx, LOCK))
		return (0);
	*philo = &td->philos[td->i];
	if (!mutex_handler(&td->td_mtx, UNLOCK))
		return (0);
	return (1);
}

void	*routine_main(void *param)
{
	t_thread_data	*td;
	t_data			*data;
	t_philo			*philo;

	td = (t_thread_data *)param;
	data = NULL;
	philo = NULL;
	if (!init_routine_data(td, &data, &philo))
		return (NULL);
	while (get_value_int(&data->start_ready_mtx, &data->start_ready) != 1)
		;
	if (!increase_value(&data->threads_counter_mtx, &data->threads_counter))
		return (NULL);
	if (!over_thinking(philo, data))
		return (NULL);
	while (!is_program_end(data))
	{
		if (get_value_int(&philo->philo_finish_mtx, &philo->philo_finish))
			break ;
		if (!eating(philo, data)
			|| !sleeping(philo, data)
			|| !thinking(philo, data))
			return (NULL);
	}
	return (NULL);
}

void	*routine_watcher(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	while (threads_ready(&data->threads_counter_mtx, data) != 1)
		;
	while (!is_program_end(data))
	{
		i = 0;
		while (i < data->philo_num && !is_program_end(data))
		{
			if (is_philo_dead(&data->philo_array[i], data))
			{
				if (!set_value_int(&data->end_program_mtx, \
					&data->end_program, 1))
					return (NULL);
				if (!print_action(DIE, &data->philo_array[i], data))
					return (NULL);
				break ;
			}
			i++;
		}
		usleep(300);
	}
	return (NULL);
}

void	*routine_one_philo(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (get_value_int(&data->start_ready_mtx, &data->start_ready) != 1)
		;
	if (!set_value_long(&data->philo_array[0].time_last_eat_mtx, \
		&data->philo_array[0].time_last_eat, get_time(MILLISECONDS)))
		return (NULL);
	if (!increase_value(&data->threads_counter_mtx, &data->threads_counter))
		return (NULL);
	print_action(TAKE_FORK, &data->philo_array[0], data);
	while (!is_program_end(data))
		usleep(100);
	return (NULL);
}
