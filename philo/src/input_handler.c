/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:37:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/11 21:23:31 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*-------------------------------*/
/*  Define forks for each philo  */
/*-------------------------------*/
void	init_philo_forks(t_data *data, int i)
{
	t_philo	*philo;

	philo = &data->philo_array[i];
	philo->fork_1 = &data->fork_array[(i + 1) % data->philo_num];
	philo->fork_2 = &data->fork_array[i];
	if (philo->id_philo % 2 == 0)
	{
		philo->fork_1 = &data->fork_array[i];
		philo->fork_2 = &data->fork_array[(i + 1) % data->philo_num];
	}
}

/*-------------------------------------------------------------*/
/*  Create data for each philo and mutexes inside philo_array  */
/*-------------------------------------------------------------*/
int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philo_array[i].id_philo = i + 1;
		data->philo_array[i].eat_counter = 0;
		data->philo_array[i].time_last_eat = 0;
		data->philo_array[i].philo_finish = 0;
		data->philo_array[i].is_error = 0;
		init_philo_forks(data, i);
		if (!mutex_handler(&data->philo_array[i].eat_counter_mtx, INIT)
			|| !mutex_handler(&data->philo_array[i].time_last_eat_mtx, INIT)
			|| !mutex_handler(&data->philo_array[i].philo_finish_mtx, INIT)
			|| !mutex_handler(&data->philo_array[i].is_error_mtx, INIT))
			return (0);
		i++;
	}
	return (1);
}

/*-----------------------------------------------------------*/
/*  Create data for each fork and mutexes inside fork_array  */
/*-----------------------------------------------------------*/
int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (!mutex_handler(&data->fork_array[i].fork, INIT))
			return (0);
		data->fork_array[i].fork_id = i;
		i++;
	}
	return (1);
}

/*------------------------------------------------*/
/*  Create data structure with input information  */
/*------------------------------------------------*/
int	init_data(t_data *data)
{
	data->philo_array = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (data->philo_array == NULL)
		return (error_malloc());
	data->fork_array = (t_fork *)malloc(sizeof(t_fork) * data->philo_num);
	if (data->fork_array == NULL)
		return (error_malloc());
	data->start_ready = 0;
	data->start_time = 0;
	data->threads_counter = 0;
	data->philos_finish = 0;
	data->finish = 0;
	if (!mutex_handler(&data->data_mtx, INIT)
		|| !mutex_handler(&data->print_mtx, INIT)
		|| !mutex_handler(&data->start_ready_mtx, INIT)
		|| !mutex_handler(&data->start_time_mtx, INIT)
		|| !mutex_handler(&data->threads_counter_mtx, INIT)
		|| !mutex_handler(&data->philos_finish_mtx, INIT)
		|| !mutex_handler(&data->finish_mtx, INIT))
		return (0);
	if (!init_fork(data)
		|| !init_philo(data))
		return (0);
	return (1);
}

/*----------------------------*/
/*  Handle input information  */
/*----------------------------*/
int	input_handler(int argc, char **argv, t_data *data)
{
	if ((argc == 6 || argc == 5) && is_correct_input(argv + 1))
	{
		if (argc == 6)
			data->eat_repeat = ft_atoi(argv[5]);
		else
			data->eat_repeat = -1;
		data->philo_num = ft_atoi(argv[1]);
		if (data->eat_repeat == 0 || data->philo_num == 0)
			return (0);
		data->time_die = ft_atoi(argv[2]) * 1000;
		data->time_eat = ft_atoi(argv[3]) * 1000;
		data->time_sleep = ft_atoi(argv[4]) * 1000;
		if (!init_data(data))
			return (error_free(data));
		return (1);
	}
	else
	{
		printf(R"\t🚧🚧🚧🚧🚧 🚨🚨🚨 Incorrect Input!!! 🚨🚨🚨 🚧🚧🚧🚧🚧\n"RES);
		printf(G"Please, follow the rules:\n\n"RES);
		printf(Y"./philo <number_of_philosophers> <time_to_die> <time_to_eat>");
		printf(" <time_to_sleep> [number_of_times_philosopher_must_eat]\n"RES);
		printf(C"For example: \"./philo 5 800 200 200 5\"\n"RES);
		return (0);
	}
}
