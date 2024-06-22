/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:47:06 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/22 19:57:51 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!input_handler(argc, argv, &data))
		return (EXIT_FAILURE);
	// struct timeval current_time;

	// // Get the current time
	// gettimeofday(&current_time, NULL);

	// // Print the current time in seconds and microseconds
	// printf("Seconds: %ld\n", current_time.tv_sec);
	// printf("Microseconds: %d\n", current_time.tv_usec);
	return (0);
}
