/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:24:05 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:24:06 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include <stdio.h>

int	builtin_env(t_env *env_list, char **args)
{
	if (!args)
		return (1);
	if (args[1])
	{
		printf("env: too many arguments\n");
		return (1);
	}
	while (env_list)
	{
		if (env_list->value && env_list->key)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
