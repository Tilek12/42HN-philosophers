/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:19:50 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 22:08:19 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*-----------------------------------*/
/*  Destroy all initialized mutexes  */
/*-----------------------------------*/
static int	destroy_mutex(t_data *data, t_thread_data **td)
{
	int	i;

	if (*td != NULL)
		if (!mutex_handler(&(*td)->td_mtx, DESTROY))
			return (0);
	i = 0;
	while (i < data->philo_num)
	{
		if (!mutex_handler(&data->philo_array[i].time_last_eat_mtx, DESTROY)
			|| !mutex_handler(&data->philo_array[i].philo_finish_mtx, DESTROY)
			|| !mutex_handler(&data->philo_array[i].eat_counter_mtx, DESTROY)
			|| !mutex_handler(&data->philo_array[i].is_error_mtx, DESTROY))
			return (0);
		i++;
	}
	if (!mutex_handler(&data->data_mtx, DESTROY)
		|| !mutex_handler(&data->print_mtx, DESTROY)
		|| !mutex_handler(&data->start_ready_mtx, DESTROY)
		|| !mutex_handler(&data->start_time_mtx, DESTROY)
		|| !mutex_handler(&data->threads_counter_mtx, DESTROY)
		|| !mutex_handler(&data->philos_finish_mtx, DESTROY)
		|| !mutex_handler(&data->finish_mtx, DESTROY))
		return (0);
	return (1);
}

/*---------------------------------------------------*/
/*  Cleanup all data after finishing the simulation  */
/*---------------------------------------------------*/
int	cleanup(t_data *data, t_thread_data **td)
{
	if (!destroy_mutex(data, td))
		return (0);
	if (*td != NULL)
	{
		free(*td);
		*td = NULL;
	}
	if (data->philo_array != NULL)
	{
		free(data->philo_array);
		data->philo_array = NULL;
	}
	if (data->fork_array != NULL)
	{
		free(data->fork_array);
		data->fork_array = NULL;
	}
	return (1);
}
