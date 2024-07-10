/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:27:53 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 22:08:05 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*---------------------------------------------*/
/*  Handle errors with printing error message  */
/*---------------------------------------------*/
int	error(char *msg)
{
	int	length;

	length = 0;
	while (msg[length])
	{
		length++;
	}
	write(2, "Error! ", 7);
	write(2, msg, length);
	write(2, "\n", 1);
	return (0);
}

/*--------------------------------------------------------------*/
/*  Write error message in case of incorrect memory allocation  */
/*--------------------------------------------------------------*/
int	error_malloc(void)
{
	write(2, "Error! ", 7);
	write(2, "Invalid memory allocation\n", 26);
	return (0);
}

/*-------------------------------------------------------------------------*/
/*  In case of error free allocated memory for philo_array and fork_array  */
/*-------------------------------------------------------------------------*/
int	error_free(t_data *data)
{
	if (data->philo_array != NULL)
	{
		free(data->philo_array);
		data->philo_array = NULL;
	}
	if (data->fork_array != NULL)
	{
		free(data->fork_array);
		data->fork_array = NULL;
	}
	return (0);
}

/*----------------------------------------------*/
/*  In case of error free all allocated memory  */
/*----------------------------------------------*/
int	error_free_all(t_data *data, t_thread_data **thread_data)
{
	if (*thread_data != NULL)
	{
		free(*thread_data);
		*thread_data = NULL;
	}
	if (data->philo_array != NULL)
	{
		free(data->philo_array);
		data->philo_array = NULL;
	}
	if (data->fork_array != NULL)
	{
		free(data->fork_array);
		data->fork_array = NULL;
	}
	return (0);
}

/*-----------------------------------------------------------------*/
/*  Check for error occures in running routine function of thread  */
/*-----------------------------------------------------------------*/
int	error_check(t_data *data)
{
	int	philo_num;
	int	i;

	philo_num = data->philo_num;
	i = 0;
	while (i < philo_num)
	{
		if (data->philo_array[i].is_error == 1)
			return (0);
		i++;
	}
	return (1);
}
