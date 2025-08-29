/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:50:35 by kkc               #+#    #+#             */
/*   Updated: 2025/08/29 21:52:51 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

long long	ft_atoll(const char *str, int *overflow)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	*overflow = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && (result > (LLONG_MAX - (*str - '0')) / 10))
			return (*overflow = 1, LLONG_MAX);
		if (sign == -1 && (-result < (LLONG_MIN + (*str - '0')) / 10))
			return (*overflow = 1, LLONG_MIN);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
