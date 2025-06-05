/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:35:19 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:35:23 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		d->philo[i].id = i + 1;
		d->philo[i].num_eats = 0;
		d->philo[i].fork_r = i - 1;
		d->philo[i].fork_l = i;
		if (handle_mutex(&d->philo[i].num_eats_mutex, INIT) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (handle_mutex(&d->philo[i].mutex_last_eat, INIT) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	d->philo[0].fork_r = d->num_philos - 1;
	return (EXIT_SUCCESS);
}

int	init_data(t_data *d)
{
	d->thread = malloc(sizeof(pthread_t *) * (d->num_philos));
	if (!d->thread)
		return (ft_malloc (d), EXIT_FAILURE);
	if (handle_mutex(&d->init_philo_mutex, INIT) == EXIT_FAILURE
		|| handle_mutex(&d->mutex_stat, INIT) == EXIT_FAILURE
		|| handle_mutex(&d->mutex_id, INIT) == EXIT_FAILURE
		|| handle_mutex(&d->mutex_msg, INIT) == EXIT_FAILURE
		|| handle_mutex(&d->mutex_fork, INIT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	d->philo = malloc(sizeof(t_philo) * d->num_philos);
	if (!d->philo)
		return (ft_malloc (d), EXIT_FAILURE);
	d->mutex = malloc(sizeof(pthread_mutex_t) * d->num_philos);
	if (!d->mutex)
		return (ft_malloc (d), EXIT_FAILURE);
	if (init_philos(d) == EXIT_FAILURE)
		return (ft_malloc (d), EXIT_FAILURE);
	d->init = true;
	return (EXIT_SUCCESS);
}

void	wait_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		handle_thread(&d->thread[i], NULL, NULL, JOIN);
		i++;
	}
}

int	start_simulation(t_data *d)
{
	if (init_data(d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_mutex(d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_mutex(&d->mutex_stat, INIT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_mutex(&d->init_philo_mutex, INIT) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_thread(d) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_mutex(&d->init_philo_mutex, LOCK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	d->init_philo = 1;
	if (handle_mutex(&d->init_philo_mutex, UNLOCK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (monitor(d) == 2)
		return (EXIT_FAILURE);
	wait_threads(d);
	return (EXIT_SUCCESS);
}

int	init(t_data *data, int ac, char **av)
{
	data->init_philo = 0;
	data->stat = 0;
	data->id = 1;
	data->num_philos = ft_atol(av[1]);
	data->time_die = ft_atol(av[2]);
	data->time_eat = ft_atol(av[3]);
	data->time_sleep = ft_atol(av[4]);
	data->max_meals = -1;
	if (ac == 6)
		data->max_meals = ft_atol(av[5]);
	data->init = false;
	data->philo = NULL;
	data->thread = NULL;
	data->mutex = NULL;
	data->s_time = current_time();
	if (start_simulation(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
