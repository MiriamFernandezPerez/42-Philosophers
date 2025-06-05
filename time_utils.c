/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:35:48 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:35:50 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	w_status(char *s, t_data *d, int i)
{
	long	time;

	handle_mutex(&d->mutex_msg, LOCK);
	time = current_time() - d->s_time;
	if (i <= d->num_philos && check_eats(d, 0, 0) == 0)
	{
		handle_mutex(&d->mutex_stat, LOCK);
		if (d->stat == 0)
			printf("\033[1;89m[%ld]	Philo [%d] \033[0;39m%s", time, i, s);
		handle_mutex(&d->mutex_stat, UNLOCK);
	}
	handle_mutex(&d->mutex_msg, UNLOCK);
}

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	wait_usleep(int time)
{
	long	start;

	start = current_time();
	while (current_time() - start < time)
	{
		usleep(time / 2);
	}
}
