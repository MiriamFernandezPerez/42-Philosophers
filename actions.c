/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:35:30 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:35:31 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_data *d, int i)
{
	int	fork1;
	int	fork2;

	fork1 = d->philo[i].fork_r;
	fork2 = d->philo[i].fork_l;
	handle_mutex(&d->mutex[fork1], LOCK);
	w_status("\033[1;94mhas taken a fork 🍴\033[0;39m\n", d, i + 1);
	if (d->num_philos == 1)
	{
		wait_usleep(d->time_die + 1);
		handle_mutex(&d->mutex[fork1], UNLOCK);
		return ;
	}
	handle_mutex(&d->mutex[fork2], LOCK);
	w_status("\033[1;94mhas taken a fork 🍴\033[0;39m\n", d, i + 1);
}

void	philo_eat(t_data *d, int i)
{
	w_status("\033[1;92mis eating 🍝\033[0;39m\n", d, i + 1);
	handle_mutex(&d->philo[i].num_eats_mutex, LOCK);
	d->philo[i].num_eats++;
	handle_mutex(&d->philo[i].num_eats_mutex, UNLOCK);
	handle_mutex(&d->philo[i].mutex_last_eat, LOCK);
	d->philo[i].last_eat = current_time() - d->s_time;
	handle_mutex(&d->philo[i].mutex_last_eat, UNLOCK);
	wait_usleep(d->time_eat);
	handle_mutex(&d->mutex[d->philo[i].fork_l], UNLOCK);
	handle_mutex(&d->mutex[d->philo[i].fork_r], UNLOCK);
}

void	philo_sleep(t_data *d, int i)
{
	w_status("\033[1;89mis sleeping 😴\033[0;39m\n", d, i + 1);
	wait_usleep(d->time_sleep);
	w_status("\033[1;95mis thinking 💭\033[0;39m\n", d, i + 1);
}
