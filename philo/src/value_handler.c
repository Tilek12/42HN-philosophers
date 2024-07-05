/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:53:21 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/04 19:15:58 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_value_int(pthread_mutex_t *mutex, int *value)
{
	int	ret_value;

	if (!mutex_handler(mutex, LOCK))
		return (-1);
	ret_value = *value;
	if (!mutex_handler(mutex, UNLOCK))
		return (-1);
	return (ret_value);
}

long	get_value_long(pthread_mutex_t *mutex, long *value)
{
	long	ret_value;

	if (!mutex_handler(mutex, LOCK))
		return (-1);
	ret_value = *value;
	if (!mutex_handler(mutex, UNLOCK))
		return (-1);
	return (ret_value);
}

int	set_value_int(pthread_mutex_t *mutex, int *variable, int value)
{
	if (!mutex_handler(mutex, LOCK))
		return (0);
	*variable = value;
	if (!mutex_handler(mutex, UNLOCK))
		return (0);
	return (1);
}

int	set_value_long(pthread_mutex_t *mutex, long *variable, long value)
{
	if (!mutex_handler(mutex, LOCK))
		return (0);
	*variable = value;
	if (!mutex_handler(mutex, UNLOCK))
		return (0);
	return (1);
}

int	is_program_end(t_data *data)
{
	if (get_value_int(&data->lock_data, &data->end_program) == -1)
		return (-1);
	else if (get_value_int(&data->lock_data, &data->end_program) == 0)
		return (0);
	else if (get_value_int(&data->lock_data, &data->end_program) == 1)
		return (1);
	else
		return (-1);
}
