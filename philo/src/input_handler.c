/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:37:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/21 11:35:42 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_philo_forks(t_data *data, int i)
{
	t_fork	*fork_first;
	t_fork	*fork_second;
	int		philo_num;
	int		philo_id;

	fork_first = data->philo_array[i].fork_1;
	fork_second = data->philo_array[i].fork_2;
	philo_num = data->philo_num;
	philo_id = data->philo_array[i].id_philo;
	fork_first = &data->fork_array[(i + 1) % philo_num];
	fork_second = &data->fork_array[i];
	if (philo_id % 2 == 0)
	{
		fork_first = &data->fork_array[i];
		fork_second = &data->fork_array[(i + 1) % philo_num];
	}
}

static void	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philo_array[i].id_philo = i + 1;
		data->philo_array[i].finish = 0;
		data->philo_array[i].eat_counter = 0;
		data->philo_array[i].finish = 0;
		init_philo_forks(data, i);
		i++;
	}
}

static int	init_fork(t_data	*data)
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

static int	init_data(int argc, char **argv, t_data *data)
{
	if (argc == 6)
		data->eat_repeat = ft_atoi(argv[5]);
	data->philo_num = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]) * 1000;
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	data->philo_array = malloc(sizeof(t_philo) * data->philo_num);
	if (data->philo_array == NULL)
		return (printf(R"Memory allocating Error!\n"RES), 0);
	data->fork_array = malloc(sizeof(t_fork) * data->philo_num);
	if (data->fork_array == NULL)
	{
		free(data->philo_array);
		return (printf(R"Memory allocating Error!\n"RES), 0);
	}
	data->end = 0;
	data->philos_ready = 0;
	if (!mutex_handler(data->block, INIT))
		return (free_exit(data));
	if (!init_fork(data))
		return (free_exit(data));
	init_philo(data);
	return (1);
}

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
		printf(R"\t🚧🚧🚧🚧🚧 🚨🚨🚨 Incorrect Input!!! 🚨🚨🚨 🚧🚧🚧🚧🚧\n"RES);
		printf(R"\t🚧🚧🚧  🚨 Include only positive numbers!!! 🚨  🚧🚧🚧\n\n"RES);
		printf(G"Please, follow the rules:\n\n"RES);
		printf(Y"\"./philo <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\"\n"RES);
		printf(C"[The last argument is optional]\n\n"RES);
		printf(G"For example: \"./philo 5 800 200 200 5\"\n"RES);
		return (0);
	}
}
