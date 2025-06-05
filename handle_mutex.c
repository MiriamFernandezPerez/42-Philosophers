/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:05:36 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 22:05:38 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		handle_mutex(&d->mutex[i], INIT);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	mutex_error(int status, t_code code)
{
	int	res;

	if (status == 0)
		return (EXIT_SUCCESS);
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		res = ft_error(VALUE_MUTEX);
	else if (status == EINVAL && code == INIT)
		res = ft_error(VALUE_ATTR);
	else if (status == EDEADLK)
		res = ft_error(DEAD);
	else if (status == EPERM)
		res = ft_error(PERM);
	else if (status == ENOMEM)
		res = ft_error(NO_MEM);
	else if (status == EBUSY)
		res = ft_error(BUSY);
	if (res == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	handle_mutex(pthread_mutex_t *mutex, t_code code)
{
	int	res;

	if (code == LOCK)
		res = mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		res = mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		res = mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		res = mutex_error(pthread_mutex_destroy(mutex), code);
	else
		res = ft_error(MUT_CODE);
	if (res == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
