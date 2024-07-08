/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:27:53 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/08 16:17:16 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_malloc(void)
{
	printf("Error! Invalid memmory allocation.\n");
	return (0);
}

int	error_free(t_data *data)
{
	if (data->philo_array != NULL)
		free(data->philo_array);
	if (data->fork_array != NULL)
		free(data->fork_array);
	return (0);
}

int	error_free_all(t_data *data, t_thread_data *thread_data)
{
	if (data->philo_array != NULL)
		free(data->philo_array);
	if (data->fork_array != NULL)
		free(data->fork_array);
	if (thread_data != NULL)
		free(thread_data);
	return (0);
}
