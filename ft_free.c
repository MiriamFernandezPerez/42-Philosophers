/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:43:30 by mirifern          #+#    #+#             */
/*   Updated: 2024/12/01 20:43:32 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_mutex(t_data *d)
{
	int	i;

	i = 0;
	if (d->mutex)
	{
		while (i < d->num_philos)
		{
			handle_mutex(&d->mutex[i], DESTROY);
			i++;
		}
		free(d->mutex);
		d->mutex = NULL;
	}
}

static void	free_philo(t_data *d)
{
	int	i;

	i = 0;
	if (d->philo)
	{
		while (i < d->num_philos)
		{
			handle_mutex(&d->philo[i].num_eats_mutex, DESTROY);
			handle_mutex(&d->philo[i].mutex_last_eat, DESTROY);
			i++;
		}
		free(d->philo);
		d->philo = NULL;
	}
}

static void	free_thread(t_data *d)
{
	int	i;

	i = 0;
	if (d->thread != NULL)
	{
		while (i < d->num_philos)
		{
			handle_thread(&d->thread[i], NULL, NULL, JOIN);
			i++;
		}
		free(d->thread);
		d->thread = NULL;
	}
}

void	ft_free(t_data *d)
{
	free_thread(d);
	free_mutex(d);
	free_philo(d);
	pthread_mutex_destroy(&d->init_philo_mutex);
	pthread_mutex_destroy(&d->mutex_stat);
	pthread_mutex_destroy(&d->mutex_id);
	pthread_mutex_destroy(&d->mutex_msg);
	pthread_mutex_destroy(&d->mutex_fork);
	free(d);
	d = NULL;
}
