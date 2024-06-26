/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:36:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/26 21:00:13 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_action(t_action action, t_philo *philo, t_data *data)
{
	int	cur_time;

	cur_time = get_time(MILLISECONDS) - data->start_time;
	if (philo->is_finish_eating)
		return (1);
	if (!mutex_handler(&data->lock_print, LOCK))
		return (0);
	if (action == TAKE_FORK && !is_program_end(data))
		printf("%d %d has taken a fork\n", cur_time, philo->id_philo);
	else if (action == EAT && !is_program_end(data))
		printf("%d %d is eating\n", cur_time, philo->id_philo);
	else if (action == SLEEP && !is_program_end(data))
		printf("%d %d is sleeping\n", cur_time, philo->id_philo);
	else if (action == THINK && !is_program_end(data))
		printf("%d %d is thinking\n", cur_time, philo->id_philo);
	else if (action == DIE && !is_program_end(data))
		printf("%d %d died\n", cur_time, philo->id_philo);
	if (!mutex_handler(&data->lock_print, UNLOCK))
		return (0);
	return (1);
}

int	eating(t_philo *philo, t_data *data)
{
	if (!mutex_handler(&philo->fork_1->fork, LOCK))
		return (0);
	if (!print_action(TAKE_FORK, philo, data))
		return (0);
	if (!mutex_handler(&philo->fork_2->fork, LOCK))
		return (0);
	if (!print_action(TAKE_FORK, philo, data))
		return (0);
	if (!set_value(&philo->lock_philo, &philo->last_eating,
		get_time(MILLISECONDS)))
		return (0);
	philo->eat_counter++;
	if (!print_action(EAT, philo, data))
		return (0);
	ft_usleep(data->time_eat, data);
	usleep(2000);
	if (data->eat_repeat > 0 && philo->eat_counter == data->eat_repeat)
	{
		if (!set_value(&philo->lock_philo, &philo->is_finish_eating, 1))
			return (0);
	}
	if (!mutex_handler(&philo->fork_1->fork, UNLOCK))
		return (0);
	if (!mutex_handler(&philo->fork_2->fork, UNLOCK))
		return (0);
	return (1);
}

int	sleeping(t_philo *philo, t_data *data)
{
	if (!print_action(THINK, philo, data))
		return (0);
	if (!ft_usleep(data->time_sleep, data))
		return (0);
	usleep(2000);
	return (1);
}

int	thinking(t_philo *philo, t_data *data)
{
	if (!print_action(THINK, philo, data))
		return (0);
	return (1);
}
