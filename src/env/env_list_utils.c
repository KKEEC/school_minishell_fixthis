/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:22:16 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:22:18 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include "../../includes/utils.h"
#include <stddef.h>
#include <stdlib.h>

static int	set_node_value(t_env *node, char *value)
{
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (0);
		}
	}
	else
		node->value = NULL;
	return (1);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	if (!key)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (!set_node_value(node, value))
		return (NULL);
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*temp;

	if (!new_node || !env_list)
		return ;
	if (!*env_list)
		*env_list = new_node;
	else
	{
		temp = *env_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}
