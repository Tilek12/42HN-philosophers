/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:37:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/03 19:40:29 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philo_array[i].id_philo = i + 1;
		data->philo_array[i].philo_finish = 0;
		data->philo_array[i].eat_counter = 0;
		data->philo_array[i].time_last_eat = get_time(MILLISECONDS);
		init_philo_forks(data, i);
		if (!mutex_handler(&data->philo_array[i].lock_philo, INIT))
			return (0);
		i++;
	}
	return (1);
}

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

int	init_data(int argc, char **argv, t_data *data)
{
	if (argc == 6)
		data->eat_repeat = ft_atoi(argv[5]);
	else
		data->eat_repeat = -1;
	data->philo_num = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]) * 1000;
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	data->philo_array = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (data->philo_array == NULL)
		return (error_malloc());
	data->fork_array = (t_fork *)malloc(sizeof(t_fork) * data->philo_num);
	if (data->fork_array == NULL)
		return (free(data->philo_array), error_malloc());
	data->end_program = 0;
	data->start_ready = 0;
	data->start_time = 0;
	data->threads_counter = 0;
	data->philos_finish = 0;
	if (!mutex_handler(&data->lock_data, INIT))
		return (error_free(data));
	if (!mutex_handler(&data->lock_print, INIT))
		return (error_free(data));
	if (!init_fork(data))
		return (error_free(data));
	if (!init_philo(data))
		return (error_free(data));
	return (1);
}

// int	init_data(int argc, char **argv, t_data *data, t_philo *philo_array)
// {
// 	data = malloc()
// 	philo_array = malloc(sizeof(t_philo) * )
// 	if (argc == 6)
// 		data->eat_repeat = ft_atoi(argv[5]);
// 	else
// 		data->eat_repeat = -1;
// 	data->philo_num = ft_atoi(argv[1]);
// 	data->time_die = ft_atoi(argv[2]) * 1000;
// 	data->time_eat = ft_atoi(argv[3]) * 1000;
// 	data->time_sleep = ft_atoi(argv[4]) * 1000;
// 	data->philo_array = malloc(sizeof(t_philo) * data->philo_num);
// 	if (data->philo_array == NULL)
// 		return (error_malloc());
// 	data->fork_array = malloc(sizeof(t_fork) * data->philo_num);
// 	if (data->fork_array == NULL)
// 		return (free(data->philo_array), error_malloc());
// 	data->end_program = 0;
// 	data->start_ready = 0;
// 	data->threads_counter = 0;
// 	// data->threads_iter = 0;
// 	data->philos_finish = 0;
// 	if (!mutex_handler(&data->lock_data, INIT))
// 		return (error_free(data));
// 	if (!mutex_handler(&data->lock_print, INIT))
// 		return (error_free(data));
// 	if (!init_fork(data))
// 		return (error_free(data));
// 	if (!init_philo(data))
// 		return (error_free(data));
// 	return (1);
// }

int	input_handler(int argc, char **argv, t_data *data)
{
	if ((argc == 6 || argc == 5) && is_correct_input(argv + 1))
	{
		if (!init_data(argc, argv, data))
			return (0);
		return (1);
	}
	else
	{
		// printf(R"\t🚧🚧🚧🚧🚧 🚨🚨🚨 Incorrect Input!!! 🚨🚨🚨 🚧🚧🚧🚧🚧\n"RES);
		// printf(R"\t🚧🚧🚧  🚨 Include only positive numbers!!! 🚨  🚧🚧🚧\n\n"RES);
		// printf(G"Please, follow the rules:\n\n"RES);
		// printf(Y"\"./philo <number_of_philosophers> <time_to_die> ");
		// printf("<time_to_eat> <time_to_sleep> ");
		// printf("[number_of_times_each_philosopher_must_eat]\"\n"RES);
		// printf(C"[The last argument is optional]\n\n"RES);
		// printf(G"For example: \"./philo 5 800 200 200 5\"\n"RES);
		printf("!!! Wrong input !!!");
		return (0);
	}
}

// int	input_handler(int argc, char **argv, t_data *data, t_philo *philo_array)
// {
// 	if ((argc == 6 || argc == 5) && is_correct_input(argv + 1))
// 	{
// 		if (!init_data(argc, argv, data, *philo_array))
// 			return (0);
// 		return (1);
// 	}
// 	else
// 	{
// 		// printf(R"\t🚧🚧🚧🚧🚧 🚨🚨🚨 Incorrect Input!!! 🚨🚨🚨 🚧🚧🚧🚧🚧\n"RES);
// 		// printf(R"\t🚧🚧🚧  🚨 Include only positive numbers!!! 🚨  🚧🚧🚧\n\n"RES);
// 		// printf(G"Please, follow the rules:\n\n"RES);
// 		// printf(Y"\"./philo <number_of_philosophers> <time_to_die> ");
// 		// printf("<time_to_eat> <time_to_sleep> ");
// 		// printf("[number_of_times_each_philosopher_must_eat]\"\n"RES);
// 		// printf(C"[The last argument is optional]\n\n"RES);
// 		// printf(G"For example: \"./philo 5 800 200 200 5\"\n"RES);
// 		printf("!!! Wrong input !!!");
// 		return (0);
// 	}
// }
