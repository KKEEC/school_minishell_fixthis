/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:24:10 by kkc               #+#    #+#             */
/*   Updated: 2025/08/29 19:32:47 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/utils.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void	numericarg_error(const char *arg)
{
	ft_printstderr("exit\n");
	ft_printstderr("bash: exit: ");
	ft_printstderr(arg);
	ft_printstderr(": numeric argument required\n");
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_number(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!is_digit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	long long	exit_code;
	int			overflow;

	exit_code = 0;
	overflow = 0;
	if (!args[1])
		return (128 + exit_code);
	if (args[2])
		return (ft_printstderr("bash: exit: too many arguments\n"), 1);
	if (!is_number(args[1]))
		return (numericarg_error(args[1]), 128 + 2);
	exit_code = ft_atoll(args[1], &overflow);
	if (overflow)
		return (numericarg_error(args[1]), 128 +2);
	ft_printstderr("exit\n");
	exit_code = ((exit_code % 256) + 256) % 256;
	return (128 + exit_code);
}
