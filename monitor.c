/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:35:30 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:35:31 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nbr_meals(t_data *d, int i, int count)
{
	handle_mutex(&d->philo[i].num_eats_mutex, LOCK);
	if (d->philo[i].num_eats == d->max_meals)
	{
		count++;
		handle_mutex(&d->philo[i].num_eats_mutex, UNLOCK);
	}
	else
		handle_mutex(&d->philo[i].num_eats_mutex, UNLOCK);
	i++;
	return (count);
}

int	check_eats(t_data *d, int i, int count)
{
	if (d->max_meals == -1)
		return (0);
	while (i < d->num_philos)
	{
		count = check_nbr_meals(d, i, count);
		i++;
	}
	if (count == i)
	{
		handle_mutex(&d->mutex_stat, LOCK);
		d->stat = 2;
		handle_mutex(&d->mutex_stat, UNLOCK);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_print_die(long t, int i)
{
	printf("\033[1;91m[%ld]	Philo [%d] \033[1;91mdied ☠️\033[0;39m\n", t, i);
}

int	check_last_eat(t_data *d, int i, long time)
{
	int	stat;

	stat = 0;
	handle_mutex(&d->philo[i].mutex_last_eat, LOCK);
	if (time - d->philo[i].last_eat > d->time_die)
	{
		handle_mutex(&d->philo[i].mutex_last_eat, UNLOCK);
		handle_mutex(&d->mutex_stat, LOCK);
		d->stat = 1;
		stat = d->stat;
		handle_mutex(&d->mutex_stat, UNLOCK);
	}
	return (stat);
}

int	monitor(t_data *d)
{
	int		i;
	long	t;

	while (1)
	{
		usleep(1000);
		i = 0;
		while (i < d->num_philos)
		{
			t = current_time() - d->s_time;
			if (check_last_eat(d, i, t) == 1)
				return (ft_print_die(t, i + 1), 2);
			handle_mutex(&d->philo[i].mutex_last_eat, UNLOCK);
			if (check_eats(d, 0, 0) == 1)
				return (2);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
