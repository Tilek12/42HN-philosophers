/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:47:06 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/29 13:30:14 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!input_handler(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!philo_start(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
