/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_withargs_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:00:20 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:00:21 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/executor.h"

static int	process_single_arg(char *arg, t_env **env_list)
{
	char	*key;

	key = extract_key(arg);
	if (!key)
		return (0);
	if (!is_valid_key(arg))
	{
		print_err_key(arg);
		free(key);
		return (1);
	}
	update_key_val(arg, key, env_list);
	free(key);
	return (0);
}

int	case_withargs_export(char **args, t_env **env_list)
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	while (args[i])
	{
		status |= process_single_arg(args[i], env_list);
		i++;
	}
	return (status);
}
