/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:27 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:22:28 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <stddef.h>
#include "../../includes/utils.h"

char	*get_env_value(t_env *env, const char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (isstrequal(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
