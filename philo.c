/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:34:50 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:34:55 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Write msn function
int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int	ft_error(char *error_msg)
{
	if (write(2, error_msg, ft_strlen(error_msg)) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_malloc(t_data *data)
{
	if (data)
		ft_free(data);
	if (ft_msn(ERR_MALL, 2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		ft_msn(ERR_ARGS, 2);
		ft_msn(NUM_PH, 2);
		ft_msn(TIMES, 2);
		return (ft_msn(OPTIONAL, 2), 1);
	}
	data = malloc(sizeof (t_data));
	if (!data)
		return (ft_malloc(data), EXIT_FAILURE);
	if (check_arg(av, ac) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init(data, ac, av) == EXIT_FAILURE)
	{
		ft_free(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
