/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/01 09:16:04 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*death_watcher(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	while (!threads_ready(&data->lock_data, data))
		;
	while (!is_program_end(data))
	{
		i = 0;
		while (i < data->philo_num && !is_program_end(data))
		{
			if (is_philo_dead(&data->philo_array[i], data))
			{
				if (!set_value_int(&data->lock_data, &data->end_program, 1))
					return (printf("set_value_int error\n"), NULL);
			}
			if (!print_action(DIE, &data->philo_array[i], data))
				return (printf("print_action error\n"), NULL);
			i++;
		}
	}
	return (NULL);
}

void	*philo_run(void *param)
{
	t_thread_data	*td;
	t_data			*data;
	t_philo			*philo;

	td = (t_thread_data *)param;
	data = td->data;
	philo = td->philo;
	while (get_value_int(&data->lock_data, &data->start_ready) != 1)
		;
	if (!set_value_long(&philo->lock_philo, &philo->time_last_eat, get_time(MILLISECONDS)))
		return (printf("set_value_long error\n"), NULL);
	if (!increase_value(&data->lock_data, &data->threads_counter))
		return (printf("Threads_counter error\n"), NULL);
	while (!is_program_end(data))
	{
		if (philo->is_finish_eating)
			break ;
		if (!eating(philo, data))
			return (printf("--- Eating error ---\n"), NULL);
		if (!sleeping(philo, data))
			return (printf("--- Sleeping error ---\n"), NULL);
		if (!thinking(philo, data))
			return (printf("--- Thinking error ---\n"), NULL);
	}
	return (NULL);
}

void	*one_philo(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	while (!threads_ready(&data->lock_data, data))
		;
	if (!set_value_long(&data->philo_array[0].lock_philo,
		&data->philo_array[0].time_last_eat, get_time(MILLISECONDS)))
		return (printf("set_value_long error\n"), NULL);
	if (!increase_value(&data->lock_data, &data->threads_counter))
		return (printf("Threads_counter error\n"), NULL);
	print_action(TAKE_FORK, &data->philo_array[0], data);
	while (!is_program_end(data))
		usleep(200);
	return (NULL);
}

int	philo_start(t_data *data)
{
	t_thread_data	*td;
	int				i;

	if (data->eat_repeat == 0)
		return (1);
	else if (data->philo_num == 1)
		thread_handler(&data->philo_array[0].id_thread, one_philo, data, CREATE);
	else
	{
		td = malloc(sizeof(t_thread_data));
		if (td == NULL)
			return (error_free(data));
		i = 0;
		while (i < data->philo_num)
		{
			td->data = data;
			td->philo = &data->philo_array[i];
			if (!thread_handler(&data->philo_array[i].id_thread, philo_run, td, CREATE))
			{
				printf(R"!!! Error pthread_create !!!\n"RES);
				free(td);
				return (error_free(data));
			}
			i++;
		}
		free(td);
	}
	// if (!thread_handler(&data->watcher, death_watcher, data, CREATE))
	// {
	// 	printf(R"!!! Error pthread_create !!!\n"RES);
	// 	return (error_free(data));
	// }
	data->start_time = get_time(MILLISECONDS);
	printf("--- start_time = %ld ---\n", data->start_time);
	if (!set_value_int(&data->lock_data, &data->start_ready, 1))
		return (error_free(data));
	i = 0;
	while (i < data->philo_num)
	{
		printf("--- START pthread_join %d --\n", i);
		if (!thread_handler(&data->philo_array[i].id_thread, NULL, NULL, JOIN))
		{
			printf(R"!!! Error pthread_join !!!\n"RES);
			free(td);
			return (error_free(data));
		}
		printf("--- END   pthread_join %d --\n", i);
		i++;
	}
	free(data->philo_array);
	free(data->fork_array);
	printf("--- Program is finished! ---\n");
	return (1);
}
