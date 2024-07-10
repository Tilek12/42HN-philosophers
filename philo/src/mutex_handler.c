/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:55 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 15:44:16 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*--------------------------------------*/
/*  Handle possible mutex usage errors  */
/*--------------------------------------*/
static int	mutex_error(int status, t_option option)
{
	if (status == 0)
		return (1);
	if (status == EINVAL && option == INIT)
		error("The value specified by attr is invalid");
	else if (status == EINVAL
		&& (option == LOCK || option == UNLOCK || option == DESTROY))
		error("The value specified by mutex is invalid");
	else if (status == EDEADLK)
	{
		error("A deadlock would occur if the thread blocked \
		waiting for mutex");
	}
	else if (status == EBUSY)
		error("Mutex is locked");
	return (0);
}

/*----------------------*/
/*  Handle mutex usage  */
/*----------------------*/
int	mutex_handler(pthread_mutex_t *mutex, t_option option)
{
	if (option == INIT)
	{
		if (!mutex_error(pthread_mutex_init(mutex, NULL), option))
			return (0);
	}
	else if (option == LOCK)
	{
		if (!mutex_error(pthread_mutex_lock(mutex), option))
			return (0);
	}
	else if (option == UNLOCK)
	{
		if (!mutex_error(pthread_mutex_unlock(mutex), option))
			return (0);
	}
	else if (option == DESTROY)
	{
		if (!mutex_error(pthread_mutex_destroy(mutex), option))
			return (0);
	}
	else
		return (error("Incorrect option for mutex_handler"));
	return (1);
}
