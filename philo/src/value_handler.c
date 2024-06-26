/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:53:21 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/26 21:00:27 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_value(pthread_mutex_t *mutex, int *value)
{
	int	ret_value;

	if (!mutex_handler(mutex, LOCK))
		return (-1);
	ret_value = *value;
	if (!mutex_handler(mutex, UNLOCK))
		return (-1);
	return (ret_value);
}

int	set_value(pthread_mutex_t *mutex, int *variable, int value)
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
	if (get_value(&data->lock_data, &data->end_program) == 0)
		return (0);
	else if (get_value(&data->lock_data, &data->end_program) == 1)
		return (1);
	else
		return (-1);
}
