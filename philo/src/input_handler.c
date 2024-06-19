/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:37:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/19 09:08:35 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i++ < data->philo_num)
	{
		philo = data->philo_array + i;
		philo->id_philo = i + 1;
		philo->finish = 0;
		philo->eat_counter = 0;
		philo->data = data;
	}
	return (1);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	i;

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
		return (printf(R"Memory allocating Error!\n"RES), 0);
	i = 0;
	while (i++ < data->philo_num)
	{
		if (!init_mutex(&data->fork_array[i].fork, INIT))
			return (free(data->philo_array), free(data->fork_array), 0);
		data->fork_array[i].fork_id = i;
	}
	if (!init_philo(data))
		return (0);
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
