/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:27:53 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/01 18:37:29 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_malloc(void)
{
	// printf(R"Error! Invalid memmory allocation.\n"RES);
	printf("Error! Invalid memmory allocation.\n");
	return (0);
}

int	error_free(t_data *data)
{
	free(data->philo_array);
	free(data->fork_array);
	return (0);
}
