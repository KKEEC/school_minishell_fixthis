/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:02:15 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:02:16 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"
#include "../../../includes/env.h"

static int	is_special_escape(char c)
{
	return (c == '"' || c == '\\' || c == '`');
}

static void	handle_quoted_escape(const char *src, size_t *i, char *result,
	size_t *j)
{
	if (is_special_escape(src[*i + 1]))
	{
		result[(*j)++] = src[*i + 1];
		*i += 2;
	}
	else
	{
		result[(*j)++] = src[(*i)++];
	}
}

char	*handle_quoted_esc_chars(const char *src, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (src[i] == '\\' && (i + 1) < len)
			handle_quoted_escape(src, &i, result, &j);
		else
			result[j++] = src[i++];
	}
	result[j] = '\0';
	return (result);
}
