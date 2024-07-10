/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:43 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 15:46:57 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*---------------------------------------*/
/*  Handle possible thread usage errors  */
/*---------------------------------------*/
static int	thread_error(int status, t_option option)
{
	if (status == 0)
		return (1);
	if (status == EAGAIN)
	{
		error("The system lacked the necessary resources to create another \
		thread, or the system-imposed limit on the total number of threads \
		in a process [PTHREAD_THREADS_MAX] would be exceeded");
	}
	else if (status == EPERM)
		error("No permission to set the required parameters");
	else if (status == EDEADLK)
	{
		error("A deadlock was detected or the value of thread specifies \
		the calling thread.\n");
	}
	else if (status == ESRCH)
	{
		error("No thread could be found corresponding to that specified \
		by the given thread ID, thread");
	}
	else if (status == EINVAL && option == CREATE)
		error("The value specified by attr is invalid");
	else if (status == EINVAL && (option == JOIN || option == DETACH))
		error("The value does not refer to a joinable thread");
	return (0);
}

/*-----------------------*/
/*  Handle thread usage  */
/*-----------------------*/
int	thread_handler(pthread_t *thread, void *(*func)(void *),
	void *param, t_option option)
{
	if (option == CREATE)
	{
		if (!thread_error(pthread_create(thread, NULL, func, param), option))
			return (0);
	}
	else if (option == JOIN)
	{
		if (!thread_error(pthread_join(*thread, NULL), option))
			return (0);
	}
	else if (option == DETACH)
	{
		if (!thread_error(pthread_detach(*thread), option))
			return (0);
	}
	else
		return (error("Incorrect option for thread_handler"));
	return (1);
}
