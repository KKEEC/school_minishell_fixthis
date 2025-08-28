/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:33 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:22:34 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include "../../includes/utils.h"
#include <stddef.h>
#include <stdlib.h>

static char	*extract_env_key(char *env_entry, char **equal_ptr)
{
	char	*equal;
	char	*key;

	if (!env_entry || !equal_ptr)
		return (NULL);
	equal = ft_strchr(env_entry, '=');
	if (!equal)
		return (NULL);
	*equal_ptr = equal;
	key = ft_strndup(env_entry, (equal - env_entry));
	return (key);
}

static int	process_env_entry(char *env_entry, t_env **env_list)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*new_node;

	if (!env_entry || !env_list)
		return (0);
	key = extract_env_key(env_entry, &equal);
	if (!key)
		return (0);
	value = ft_strdup(equal + 1);
	if (!value)
	{
		free(key);
		return (0);
	}
	new_node = new_env_node(key, value);
	free(key);
	free(value);
	if (!new_node)
		return (0);
	add_env_node(env_list, new_node);
	return (1);
}

t_env	*init_env_list(char **envp, t_env **env_list)
{
	int	i;

	if (!envp || !env_list)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		process_env_entry(envp[i], env_list);
		i++;
	}
	return (*env_list);
}
