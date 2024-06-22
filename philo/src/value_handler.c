/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:53:21 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/22 15:33:37 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_value(pthread_mutex_t *mutex, int *value, t_data *data)
{
	int	ret_value;

	if (!mutex_handler(mutex, LOCK))
		return (-1);
	ret_value = *value;
	if (!mutex_handler(mutex, UNLOCK))
		return (-1);
	return (ret_value);
}

int	set_value(pthread_mutex_t *mutex, int *variable, int value, t_data *data)
{
	if (!mutex_handler(mutex, LOCK))
		return (exit_free(data));
	*variable = value;
	if (!mutex_handler(mutex, UNLOCK))
		return (exit_free(data));
	return (1);
}

int	is_finished(t_data *data)
{
	if (get_value(data->block, &data->end, data) == 0)
		return (0);
	else if (get_value(data->block, &data->end, data) == 1)
		return (1);
	else if (get_value(data->block, &data->end, data) == -1)
		return (-1);
}
