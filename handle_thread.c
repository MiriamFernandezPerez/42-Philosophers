/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:05:59 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 22:06:00 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		if (pthread_mutex_lock(&d->philo[i].mutex_last_eat) == (EXIT_FAILURE))
			return (EXIT_FAILURE);
		d->philo[i].last_eat = 0;
		if (pthread_mutex_unlock(&d->philo[i].mutex_last_eat) == (EXIT_FAILURE))
			return (EXIT_FAILURE);
		if (handle_thread(&d->thread[i], &routine, (void *)d, CREATE) == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	thread_error(int status, t_code code)
{
	int	res;

	if (status == 0)
		return (EXIT_SUCCESS);
	if (status == EAGAIN)
		res = ft_error(AGAIN);
	else if (status == EPERM)
		res = ft_error(NO_PERM);
	else if (status == EINVAL && code == CREATE)
		res = ft_error(VALUE_ATTR);
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		res = ft_error(NO_JOIN);
	else if (status == ESRCH)
		res = ft_error(SRCH);
	else if (status == EDEADLK)
		res = ft_error(DEADLK);
	if (res == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_thread(pthread_t *th, void *(*f)(void *), void *data, t_code c)
{
	int	res;

	if (c == CREATE)
		res = thread_error(pthread_create(th, NULL, f, data), c);
	else if (c == JOIN)
		res = thread_error(pthread_join(*th, NULL), c);
	else if (c == DETACH)
		res = thread_error(pthread_detach(*th), c);
	else
		res = ft_error(TH_CODE);
	if (res == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
