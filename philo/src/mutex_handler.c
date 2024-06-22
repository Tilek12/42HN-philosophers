/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:55 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/19 09:55:48 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	mutex_error(int status, t_option option)
{
	if (status == 0)
		return (1);
	if (status == EINVAL && option == INIT)
		printf(R"Error! The value specified by attr is invalid.\n"RES);
	else if (status == EINVAL
		&& (option == LOCK || option == UNLOCK || option == DESTROY))
		printf(R"Error! The value specified by mutex is invalid.\n"RES);
	else if (status == EDEADLK)
	{
		printf(R"Error! A deadlock would occur if the thread blocked \
		waiting for mutex.\n"RES);
	}
	else if (status == EBUSY)
		printf(R"Error! Mutex is locked.\n"RES);
	return (0);
}

int	mutex_handler(pthread_mutex_t *mutex, t_option option)
{
	if (option == INIT)
	{
		if (!error_mutex(pthread_mutex_init(mutex, NULL), option))
			return (0);
	}
	else if (option == LOCK)
	{
		if (!error_mutex(pthread_mutex_lock(mutex), option))
			return (0);
	}
	else if (option == UNLOCK)
	{
		if (!error_mutex(pthread_mutex_unlock(mutex), option))
			return (0);
	}
	else if (option == DESTROY)
	{
		if (!error_mutex(pthread_mutex_destroy(mutex), option))
			return (0);
	}
	else
		return (printf(R"Error! Incorrect option for mutex_init.\n"RES), 0);
	return (1);
}
