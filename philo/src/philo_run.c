/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/22 18:02:11 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_time(t_time_def time_def, t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error_free(data));
	if (time_def == MICROSECONDS)
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else if (time_def == MILLISECONDS)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else
		return (error_free(data));
}

void	philo_run(void *param)
{

}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	if (data->eat_repeat == 0)
		return (1);
	else if (data->philo_num == 1)
		;
	else
	{
		while (i < data->philo_num)
		{
			if (!thread_handler(&data->philo_array[i].id_thread,
				philo_run, &data->philo_array[i], CREATE))
				retutn (0);
			i++;
		}
	}
	if (!set_value(&data->block, &data->philos_ready, 1, data))
		return (error_free(data));
	return (1);
}
