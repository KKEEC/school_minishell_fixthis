/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:49:01 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:49:03 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"
#include "../../../includes/env.h"

static int	is_escaped(const char *input, size_t i)
{
	int	backslash;

	backslash = 0;
	while (i > 0 && input[--i] == '\\')
		backslash++;
	if (backslash % 2 == 0)
		return (0);
	else
		return (1);
}

static void	find_closing_quote(const char *input, size_t *i)
{
	while (input[(*i)])
	{
		if (input[*i] == '"' && !is_escaped(input, *i))
			break ;
		(*i)++;
	}
}

char	*handle_double_quote(const char *input, size_t *i, t_env *env_list,
	int *status)
{
	int		start;
	char	*word;
	char	*expanded_val;

	start = ++(*i);
	find_closing_quote(input, i);
	if (input[*i] != '"')
		return (NULL);
	word = ft_strndup(&input[start], *i - start);
	(*i)++;
	if (!word)
		return (NULL);
	expanded_val = expanddollar(word, env_list, status);
	free(word);
	return (expanded_val);
}
