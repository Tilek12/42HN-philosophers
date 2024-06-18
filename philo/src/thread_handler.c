/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:43 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/18 16:35:00 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	error_thread(int status, t_option option)
{
	if (status == 0)
		return (1);
	if (status == EAGAIN)
	{
		printf(R"Error! The system lacked the necessary resources to create \
		another thread, or the system-imposed limit on the total number of \
		threads in a process [PTHREAD_THREADS_MAX] would be exceeded.\n"RES);
	}
	else if (status == EPERM)
	{
		printf(R"Error! The caller does not have appropriate permission to \
		set the required scheduling parameters or scheduling policy.\n"RES);
	}
	else if (status == EDEADLK)
	{
		printf(R"Error! A deadlock was detected or the value of thread \
		specifies the calling thread.\n"RES);
	}
	else if (status == ESRCH)
	{
		printf(R"Error! No thread could be found corresponding to that \
		specified by the given thread ID, thread.\n"RES);
	}
	else if (status == EINVAL && option == CREATE)
		printf(R"Error! The value specified by attr is invalid.\n"RES);
	else if (status == EINVAL && (option == JOIN || option == DETACH))
	{
		printf(R"Error! The implementation has detected that the value \
		specified by thread does not refer to a joinable thread.\n"RES);
	}
	return (0);
}

int	init_thread(pthread_t thread, void *(*func)(void *),
	void *data, t_option option)
{
	if (option == CREATE)
	{
		if (!error_thread(pthread_create(thread, NULL, func, data), option))
			return (0);
	}
	else if (option == JOIN)
	{
		if (!error_thread(pthread_join(thread, NULL), option))
			return (0);
	}
	else if (option == DETACH)
	{
		if (!error_thread(pthread_detach(thread), option))
			return (0);
	}
	else
		return (printf("Error! Incorrect option for thread_init.\n"), 0);
	return (1);
}