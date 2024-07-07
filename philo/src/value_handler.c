/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:53:21 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/05 18:22:48 by tkubanyc         ###   ########.fr       */
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

int	increase_value(pthread_mutex_t *mutex, int *value)
{
	if (!mutex_handler(mutex, LOCK))
		return (0);
	(*value)++;
	if (!mutex_handler(mutex, UNLOCK))
		return (0);
	return (1);
}
