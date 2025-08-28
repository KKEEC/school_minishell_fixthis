/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:00:05 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:00:14 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/executor.h"
#include "../../../../includes/utils.h"

int	builtin_export(char **args, t_env **env_list)
{
	if (!args[1])
	{
		case_noargs_export(*env_list);
		return (0);
	}
	return (case_withargs_export(args, env_list));
}
