/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:43 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/06 13:53:03 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static int	thread_error(int status, t_option option)
// {
// 	if (status == 0)
// 		return (1);
// 	if (status == EAGAIN)
// 	{
// 		printf(R"Error! The system lacked the necessary resources to create
// 		another thread, or the system-imposed limit on the total number of
// 		threads in a process [PTHREAD_THREADS_MAX] would be exceeded.\n"RES);
// 	}
// 	else if (status == EPERM)
// 		printf(R"Error! No permission to set the required parameters \n"RES);
// 	else if (status == EDEADLK)
// 	{
// 		printf(R"Error! A deadlock was detected or the value of thread
// 		specifies the calling thread.\n"RES);
// 	}
// 	else if (status == ESRCH)
// 	{
// 		printf(R"Error! No thread could be found corresponding to that
// 		specified by the given thread ID, thread.\n"RES);
// 	}
// 	else if (status == EINVAL && option == CREATE)
// 		printf(R"Error! The value specified by attr is invalid.\n"RES);
// 	else if (status == EINVAL && (option == JOIN || option == DETACH))
// 		printf(R"Error! The value does not refer to a joinable thread.\n"RES);
// 	return (0);
// }

// int	thread_handler(pthread_t *thread, void *(*func)(void *),
// 	void *param, t_option option)
// {
// 	if (option == CREATE)
// 	{
// 		if (!thread_error(pthread_create(thread, NULL, func, param), option))
// 			return (0);
// 	}
// 	else if (option == JOIN)
// 	{
// 		if (!thread_error(pthread_join(*thread, NULL), option))
// 			return (0);
// 	}
// 	else if (option == DETACH)
// 	{
// 		if (!thread_error(pthread_detach(*thread), option))
// 			return (0);
// 	}
// 	else
// 		return (printf(R"Error! Incorrect option for thread_init.\n"RES), 0);
// 	return (1);
// }

static int	thread_error(int status, t_option option)
{
	if (status == 0)
		return (1);
	if (status == EAGAIN)
	{
		printf("Error!\n");
	}
	else if (status == EPERM)
		printf("Error! No permission to set the required parameters \n");
	else if (status == EDEADLK)
	{
		printf("Error!\n");
	}
	else if (status == ESRCH)
	{
		printf("Error!\n");
	}
	else if (status == EINVAL && option == CREATE)
		printf("Error! The value specified by attr is invalid.\n");
	else if (status == EINVAL && (option == JOIN || option == DETACH))
		printf("Error! The value does not refer to a joinable thread.\n");
	return (0);
}

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
		return (printf("Error! Incorrect option for thread_init.\n"), 0);
	return (1);
}
