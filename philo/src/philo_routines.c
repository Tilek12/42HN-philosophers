/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:48:57 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 16:54:48 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*----------------------------------------------*/
/*  Initialize data for routine_philo function  */
/*----------------------------------------------*/
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

/*---------------------------------------------------------*/
/*  Catch the error in running routine function of thread  */
/*---------------------------------------------------------*/
void	error_catcher(t_philo *philo)
{
	set_value_int(&philo->is_error_mtx, &philo->is_error, 1);
}

/*---------------------------------------------*/
/*  Routine function of thread for each philo  */
/*---------------------------------------------*/
void	*routine_philo(void *param)
{
	t_thread_data	*td;
	t_data			*data;
	t_philo			*philo;

	td = (t_thread_data *)param;
	data = NULL;
	philo = NULL;
	if (!init_routine_data(td, &data, &philo))
		return (error_catcher(philo), NULL);
	while (get_value_int(&data->start_ready_mtx, &data->start_ready) != 1)
		;
	if (!increase_value(&data->threads_counter_mtx, &data->threads_counter))
		return (error_catcher(philo), NULL);
	if (!over_thinking(philo, data))
		return (error_catcher(philo), NULL);
	while (!is_program_end(data))
	{
		if (get_value_int(&philo->philo_finish_mtx, &philo->philo_finish))
			break ;
		if (!eating(philo, data)
			|| !sleeping(philo, data)
			|| !thinking(philo, data))
			return (error_catcher(philo), NULL);
	}
	return (NULL);
}

/*--------------------------------------------------------------*/
/*  Watcher routine function of thread for searching errors,    */
/*  dead philosophers and stop the simulation if all             */
/*  philosophers ate number_of_times_each_philosopher_must_eat  */
/*--------------------------------------------------------------*/
void	*routine_watcher(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	while (threads_ready(&data->threads_counter_mtx, data) != 1)
		;
	while (!is_program_end(data))
	{
		i = -1;
		while (++i < data->philo_num && !is_program_end(data))
		{
			if (is_philo_error(&data->philo_array[i])
				|| is_philo_dead(&data->philo_array[i], data))
			{
				if (!set_value_int(&data->finish_mtx, &data->finish, 1))
					return (error_catcher(&data->philo_array[i]), NULL);
				if (is_philo_dead(&data->philo_array[i], data))
					if (!print_action(DIE, &data->philo_array[i], data))
						return (error_catcher(&data->philo_array[i]), NULL);
				break ;
			}
		}
		usleep(300);
	}
	return (NULL);
}

/*-----------------------------------------------------------------------*/
/*  Routine function of thread if there is only one philo in simulation  */
/*-----------------------------------------------------------------------*/
void	*routine_one_philo(void *param)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)param;
	philo = &data->philo_array[0];
	while (get_value_int(&data->start_ready_mtx, &data->start_ready) != 1)
		;
	if (!set_value_long(&philo->time_last_eat_mtx, &philo->time_last_eat, \
		get_time(MILLISECONDS)))
		return (error_catcher(philo), NULL);
	if (!increase_value(&data->threads_counter_mtx, &data->threads_counter))
		return (error_catcher(philo), NULL);
	if (!print_action(TAKE_FORK, &data->philo_array[0], data))
		return (error_catcher(philo), NULL);
	while (!is_program_end(data))
		usleep(300);
	return (NULL);
}
