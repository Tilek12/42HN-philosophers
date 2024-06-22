/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:39 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/21 12:13:19 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_time(t_time time, t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (free_exit(data));
	if (time == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else if (time == MILLISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else
		return (free_exit(data));
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
	return (1);
}
