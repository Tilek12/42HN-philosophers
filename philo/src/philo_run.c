/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/04 19:40:55 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*death_watcher(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	while (threads_ready(&data->lock_data, data) != 1)
		;
	while (!is_program_end(data))
	{
		i = 0;
		while (i < data->philo_num && !is_program_end(data))
		{
			if (is_philo_dead(&data->philo_array[i], data))
			{
				if (!set_value_int(&data->lock_data, &data->end_program, 1))
					return (printf("!!! Error set_value - end_program !!!\n"), NULL);
				if (!print_action(DIE, &data->philo_array[i], data))
					return (printf("!!! Error print_action - died !!!\n"), NULL);
				break ;
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	over_thinking(t_philo *philo, t_data *data)
{
	if (data->philo_num % 2 == 0)
	{
		if (philo->id_philo % 2 == 0)
		{
			if (!thinking(philo, data) || !ft_usleep(100, data))
				return (0);
		}
	}
	else
	{
		if (philo->id_philo % 2)
		{
			if (!thinking(philo, data))
				return (0);
		}
	}
	return (1);
}

void	*philo_run(void *param)
{
	t_thread_data	*td;
	t_data			*data;
	t_philo			*philo;
	// long			start_time;

	td = (t_thread_data *)param;
	philo = (t_philo *)param;
	pthread_mutex_lock(&td->data->lock_data);
	data = td->data;
	pthread_mutex_lock(&td->lock_td);
	philo = &td->philos[td->i];
	pthread_mutex_unlock(&td->lock_td);
	pthread_mutex_unlock(&td->data->lock_data);
	// printf("-- time_die = %d --\n", data->time_die);
	// printf("-- id_philo = %d --\n", philo->id_philo);
	// data = philo->data;
	while (get_value_int(&data->lock_data, &data->start_ready) != 1)
		;
	// start_time = get_time(MILLISECONDS);
	if (!set_value_long(&philo->lock_philo, &philo->time_last_eat,
			get_value_long(&data->lock_data, &data->start_time)))
		return (NULL);
	// if (start_time == -1)
	// 	return (NULL);
	// if (!set_value_long(&data->lock_data, &data->start_time, start_time))
	// 	return (NULL);
	// pthread_mutex_lock(&philo->lock_philo);
	// pthread_mutex_lock(&data->lock_print);
	// printf("- philo [%d], time_last_eat = %ld -\n", philo->id_philo, philo->time_last_eat);
	// pthread_mutex_unlock(&data->lock_print);
	// pthread_mutex_unlock(&philo->lock_philo);
	if (!increase_value(&data->lock_data, &data->threads_counter))
		return (printf("!!! Error increase_value - threads_counter !!!\n"), NULL);
	if (!over_thinking(philo, data))
		return (printf("!!! Error over_thinking !!!\n"), NULL);
	while (!is_program_end(data))
	{
		int	is_philo_finish = get_value_int(&philo->lock_philo, &philo->philo_finish);
		if (is_philo_finish == -1)
			return (printf("Error get_value_int - philo_finish\n"), NULL);
		else if (is_philo_finish == 1)
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
	while (get_value_int(&data->lock_data, &data->start_ready) != 1)
		;
	if (!set_value_long(&data->philo_array[0].lock_philo,
		&data->philo_array[0].time_last_eat, get_time(MILLISECONDS)))
		return (printf("!!! Error philo - set_value_long - time_last_eat !!!\n"), NULL);
	if (!increase_value(&data->lock_data, &data->threads_counter))
		return (printf("!!! Error increase_value - threads_counter !!!\n"), NULL);
	print_action(TAKE_FORK, &data->philo_array[0], data);
	while (!is_program_end(data))
		usleep(100);
	return (NULL);
}

int	philo_start(t_data *data)
{
	t_thread_data	*td;
	// long			start_time;
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
		pthread_mutex_lock(&data->lock_data);
		td->data = data;
		td->philos = data->philo_array;
		pthread_mutex_unlock(&data->lock_data);
		mutex_handler(&td->lock_td, INIT);
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&td->lock_td);
			td->i = i;
			pthread_mutex_unlock(&td->lock_td);
			if (!thread_handler(&td->philos[i].id_thread, philo_run, td, CREATE))
			// if (!thread_handler(&data->philo_array[i].id_thread, philo_run, &data->philo_array[i], CREATE))
			{
				printf("!!! Error philo[%d] pthread_create !!!\n", (i + 1));
				free(td);
				return (error_free(data));
			}
			// printf("id_philo = %d\n", td->philos[i].id_philo);
			usleep(100);
			i++;
		}
	}
	if (!thread_handler(&data->watcher, death_watcher, data, CREATE))
	{
		printf("!!! Error death_watcher - pthread_create !!!\n");
		return (error_free(data));
	}
	// start_time = get_time(MILLISECONDS);
	// if (start_time == -1)
	// {
	// 	free(td);
	// 	return (error_free(data));
	// }
	// if (!set_value_long(&data->lock_data, &data->start_time, start_time))
	// {
	// 	free(td);
	// 	return (error_free(data));
	// }
	// i = 0;
	// while (i < data->philo_num)
	// {
	// 	if (!set_value_long(&data->philo_array[i].lock_philo,
	// 		&data->philo_array[i].time_last_eat, start_time))
	// 	{
	// 		free(td);
	// 		return (error_free(data));
	// 	}
	// 	i++;
	// }
	// if (!set_value_int(&data->lock_data, &data->start_ready, 1))
	// {
	// 	free(td);
	// 	return (error_free(data));
	// }
	pthread_mutex_lock(&data->lock_data);
	data->start_ready = 1;
	data->start_time = get_time(MILLISECONDS);
	pthread_mutex_unlock(&data->lock_data);

	// printf("--- start_time = %ld ---\n", data->start_time);
	i = 0;
	while (i < data->philo_num)
	{
		// printf("--- START pthread_join %d --\n", i);
		if (!thread_handler(&data->philo_array[i].id_thread, NULL, NULL, JOIN))
		{
			printf("!!! Error philo[%d] pthread_join !!!\n", (i + 1));
			free(td);
			return (error_free(data));
		}
		// printf("--- END   pthread_join %d --\n", i);
		i++;
	}
	if (!set_value_int(&data->lock_data, &data->end_program, 1))
	{
		printf("!!! Error set_value - end_program !!!\n");
		free(td);
		return (error_free(data));
	}
	if (!thread_handler(&data->watcher, NULL, NULL, JOIN))
	{
		printf("!!! Error death_watcher - pthread_join !!!\n");
		free(td);
		return (error_free(data));
	}
	free(td);
	if (!cleanup(data))
		return (error_free(data));
	// printf("--- Program is finished! ---\n");
	return (1);
}
