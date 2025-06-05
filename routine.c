/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:40:03 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:40:04 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_data *d)
{
	int	ret;

	pthread_mutex_lock(&d->mutex_stat);
	ret = d->stat;
	pthread_mutex_unlock(&d->mutex_stat);
	return (ret);
}

int	philo_routine(t_data *d)
{
	int	i;

	handle_mutex(&d->mutex_id, LOCK);
	i = d->id - 1;
	d->id++;
	handle_mutex(&d->mutex_id, UNLOCK);
	if (d->num_philos == 1)
	{
		w_status("\033[1;94mhas taken a fork 🍴\033[0;39m\n", d, i + 1);
		wait_usleep(d->time_die);
		return (EXIT_FAILURE);
	}
	if (i % 2 == 0)
		wait_usleep(d->time_eat / 2);
	while (check_status(d) == 0)
	{
		take_fork(d, i);
		philo_eat(d, i);
		philo_sleep(d, i);
	}
	return (EXIT_SUCCESS);
}

void	*routine(void *f)
{
	t_data	*d;
	int		init_value;

	d = (t_data *)f;
	while (1)
	{
		handle_mutex(&d->init_philo_mutex, LOCK);
		init_value = d->init_philo;
		handle_mutex(&d->init_philo_mutex, UNLOCK);
		if (init_value == 1)
			break ;
		wait_usleep(10);
	}
	if (philo_routine(d) == -1)
		return (NULL);
	return (NULL);
}
