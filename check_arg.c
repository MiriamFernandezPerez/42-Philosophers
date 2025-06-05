/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:35:07 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/19 20:35:09 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*check_input(char *str)
{
	int		i;
	char	*nb;

	i = 0;
	while (ft_isspace(str[i]))
		++str;
	if (str[i] == '+')
		++str;
	else if (str[i] == '-')
		return (ft_msn(NEG, 2), NULL);
	if (!str[i])
		return (ft_msn(NOT_DIG, 2), NULL);
	nb = str;
	return (nb);
}

long	ft_atol(char *str)
{
	long int	nb;
	int			sign;

	nb = 0;
	sign = 1;
	str = check_input(str);
	if (str == NULL)
		return (-1);
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (check_limits(nb))
		return (-1);
	return (sign * nb);
}

int	check_digits(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			i++;
		else
			return (ft_msn(NOT_DIG, 2), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_arg(char **av, int ac)
{
	int			i;
	long int	res;

	i = 0;
	i++;
	while (i < ac)
	{
		res = ft_atol(av[i]);
		if (res == -1)
			exit (EXIT_FAILURE);
		if (check_digits(av[i]) == 1)
			exit (EXIT_FAILURE);
		if (res <= 0)
		{
			if (res == 0)
				ft_msn(ZERO, 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
