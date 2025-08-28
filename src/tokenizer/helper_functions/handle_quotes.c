/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:49:23 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:49:38 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"

char	*handle_single_quote(const char *input, size_t *i)
{
	int		start;
	char	*word;

	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
		return (NULL);
	word = ft_strndup(&input[start], *i - start);
	(*i)++;
	if (!word)
		return (NULL);
	return (word);
}
