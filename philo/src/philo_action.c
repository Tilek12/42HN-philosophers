/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:36:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 17:44:17 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*-----------------------------------------*/
/*  Print current action of certain philo  */
/*-----------------------------------------*/
int	print_action(t_action action, t_philo *philo, t_data *data)
{
	long	time_program;

	if (!mutex_handler(&data->print_mtx, LOCK))
		return (0);
	time_program = life_time_program(data);
	if (action == DIE)
		printf("%ld %d died\n", time_program, philo->id_philo);
	else if (action == TAKE_FORK && !is_program_end(data))
		printf("%ld %d has taken a fork\n", time_program, philo->id_philo);
	else if (action == EAT && !is_program_end(data))
		printf("%ld %d is eating\n", time_program, philo->id_philo);
	else if (action == SLEEP && !is_program_end(data))
		printf("%ld %d is sleeping\n", time_program, philo->id_philo);
	else if (action == THINK && !is_program_end(data))
		printf("%ld %d is thinking\n", time_program, philo->id_philo);
	if (!mutex_handler(&data->print_mtx, UNLOCK))
		return (0);
	return (1);
}

/*-----------------------------------------*/
/*  Start eating action for certain philo  */
/*-----------------------------------------*/
int	eating(t_philo *philo, t_data *data)
{
	if (!mutex_handler(&philo->fork_1->fork, LOCK)
		|| !print_action(TAKE_FORK, philo, data)
		|| !mutex_handler(&philo->fork_2->fork, LOCK)
		|| !print_action(TAKE_FORK, philo, data)
		|| !set_value_long(&philo->time_last_eat_mtx, &philo->time_last_eat,
			get_time(MILLISECONDS))
		|| !print_action(EAT, philo, data)
		|| !ft_usleep((long)data->time_eat, data))
		return (0);
	usleep(1);
	if (!increase_value(&philo->eat_counter_mtx, &philo->eat_counter))
		return (0);
	if (data->eat_repeat > 0 && is_philo_finish(philo, data) == 1)
	{
		if (!set_value_int(&philo->philo_finish_mtx, &philo->philo_finish, 1)
			|| !increase_value(&data->philos_finish_mtx, &data->philos_finish))
			return (0);
		if (is_all_finish(data))
			if (!set_value_int(&data->finish_mtx, &data->finish, 1))
				return (0);
	}
	if (!mutex_handler(&philo->fork_1->fork, UNLOCK)
		|| !mutex_handler(&philo->fork_2->fork, UNLOCK))
		return (0);
	return (1);
}

/*-------------------------------------------*/
/*  Start sleeping action for certain philo  */
/*-------------------------------------------*/
int	sleeping(t_philo *philo, t_data *data)
{
	if (!print_action(SLEEP, philo, data))
		return (0);
	if (!ft_usleep((long)data->time_sleep, data))
		return (0);
	return (1);
}

/*-------------------------------------------*/
/*  Start thinking action for certain philo  */
/*-------------------------------------------*/
int	thinking(t_philo *philo, t_data *data)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;
	long	time_die;

	if (!print_action(THINK, philo, data))
		return (0);
	time_eat = (long)data->time_eat;
	time_sleep = (long)data->time_sleep;
	time_die = (long)data->time_die;
	time_think = time_die - time_eat - time_sleep;
	if (time_think <= 0)
		return (1);
	else
		ft_usleep((time_think * 0.5), data);
	return (1);
}

/*-----------------------------------------------------------------------*/
/*  Start thinking action for certain philo at the start of the program  */
/*-----------------------------------------------------------------------*/
int	over_thinking(t_philo *philo, t_data *data)
{
	if (data->philo_num % 2 == 0)
	{
		if (philo->id_philo % 2 == 0)
		{
			if (!thinking(philo, data))
				return (0);
		}
	}
	else
	{
		if (philo->id_philo % 2)
		{
			if (!thinking(philo, data))
				return (0);
		}
	}
	return (1);
}
