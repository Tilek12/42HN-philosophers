/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:44:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/06/18 12:07:20 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*------------------------------------------------------*/
/*  Checks if the character is a new line, space, tab,  */
/*  the start or the end of line.                       */
/*------------------------------------------------------*/
static int	is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

/*------------------------------------------*/
/*  Checks if the the character is a digit  */
/*------------------------------------------*/
static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*-----------------------------*/
/*  Changes string to integer  */
/*-----------------------------*/
int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (is_digit(str[i]))
			result = (result * 10) + (str[i] - '0');
		else
			return (-1);
		i++;
	}
	if (result > INT_MAX)
		return (-1);
	else
		return (result);
}

/*-----------------------------------------------*/
/*  Checks if the only spaces are in the string  */
/*-----------------------------------------------*/
static int	is_spaces_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_correct_input(char **str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i])
	{
		if (is_spaces_only(str[i]))
			return (0);
		num = ft_atoi(str[i]);
		if (num == -1)
			return (0);
		i++;
	}
	return (1);
}
