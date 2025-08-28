/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:48:18 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:48:19 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../includes/env.h"

t_token	*tokenize(const char *input, t_env *env_list, int *status)
{
	t_token			*tokens;
	size_t			i;
	char			*acc;
	t_tokenize_ctx	ctx;

	tokens = NULL;
	i = 0;
	acc = NULL;
	if (!input)
		return (NULL);
	ctx.input = input;
	ctx.i = &i;
	ctx.acc = &acc;
	ctx.tokens = &tokens;
	ctx.env_list = env_list;
	ctx.status = status;
	tokenize_loop(&ctx);
	return (finalize_tokenization(&ctx));
}
