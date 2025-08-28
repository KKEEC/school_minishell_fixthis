/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:42 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:22:43 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include <stddef.h>
#include <stdlib.h>
#include "../../includes/utils.h"

static t_env	*create_env_node(const char *key, const char *value);

inline
static void	handle_empty_env(t_env **env_list,
		const char *key,
		const char *value)
{
	*env_list = create_env_node(key, value);
}

inline
static int	handle_key_exist(t_env *current, const char *key, const char *value)
{
	char	*new_value;

	if (isstrequal(current->key, key))
	{
		if (value)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (1);
			free(current->value);
			current->value = new_value;
		}
		else
		{
			free(current->value);
			current->value = NULL;
		}
		return (1);
	}
	return (0);
}

static t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	update_env(t_env **env_list, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (!key)
		return ;
	if (!*env_list)
	{
		handle_empty_env(env_list, key, value);
		return ;
	}
	current = *env_list;
	while (current)
	{
		if (handle_key_exist(current, key, value))
			return ;
		if (!current->next)
			break ;
		current = current->next;
	}
	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	current->next = new_node;
}
