/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_end_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:32:06 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/10 16:42:11 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*--------------------------------------------------------------------------*/
/*  Check if certain philo has error in running routine function of thread  */
/*--------------------------------------------------------------------------*/
int	is_philo_error(t_philo *philo)
{
	return (get_value_int(&philo->is_error_mtx, &philo->is_error));
}

/*----------------------------------*/
/*  Check if certain philo is dead  */
/*----------------------------------*/
int	is_philo_dead(t_philo *philo, t_data *data)
{
	long	time_life;
	long	time_die;

	if (get_value_int(&philo->philo_finish_mtx, &philo->philo_finish))
		return (0);
	time_life = life_time_philo(philo);
	time_die = (long)(data->time_die / 1000);
	if (time_life >= time_die)
		return (1);
	return (0);
}

/*------------------------------------------------------------------------*/
/*  Check if certain philo ate number_of_times_each_philosopher_must_eat  */
/*------------------------------------------------------------------------*/
int	is_philo_finish(t_philo *philo, t_data *data)
{
	int	eat_counter;
	int	eat_repeat;

	eat_counter = get_value_int(&philo->eat_counter_mtx, &philo->eat_counter);
	eat_repeat = data->eat_repeat;
	if (eat_counter == -1 || eat_repeat == -1)
		return (-1);
	if (eat_counter == eat_repeat)
		return (1);
	return (0);
}

/*---------------------------------------------------------------------------*/
/*  Check if all philosophers ate number_of_times_each_philosopher_must_eat  */
/*---------------------------------------------------------------------------*/
int	is_all_finish(t_data *data)
{
	int	philos_finish;
	int	philo_num;

	philos_finish = get_value_int(&data->philos_finish_mtx, \
									&data->philos_finish);
	if (philos_finish == -1)
		return (-1);
	philo_num = data->philo_num;
	if (philos_finish == philo_num)
		return (1);
	return (0);
}

/*-------------------------------------------------------*/
/*  Get the value of finish variable in data structure.  */
/*  Value equals to 1 means the end of the simulation.   */
/*-------------------------------------------------------*/
int	is_program_end(t_data *data)
{
	return (get_value_int(&data->finish_mtx, &data->finish));
}
