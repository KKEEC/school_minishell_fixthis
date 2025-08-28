/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:48:29 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:48:31 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../includes/env.h"

void	process_character(t_tokenize_ctx *ctx)
{
	if (ft_isspace(ctx->input[*ctx->i]))
		handle_whitespace(ctx);
	else if (!ft_isschar(ctx->input[*ctx->i])
		&& ctx->input[*ctx->i] != '\'' && ctx->input[*ctx->i] != '"')
	{
		if (!handle_word_accumulation(ctx))
			return ;
	}
	else if (ctx->input[*ctx->i] == '\'' || ctx->input[*ctx->i] == '"')
	{
		if (!handle_quote_accumulation(ctx))
			return ;
	}
	else
		handle_special_finalize(ctx);
}

void	tokenize_loop(t_tokenize_ctx *ctx)
{
	while (ctx->input[*ctx->i])
		process_character(ctx);
}

t_token	*finalize_tokenization(t_tokenize_ctx *ctx)
{
	if (*ctx->acc && (*ctx->acc)[0] != '\0')
		add_token(ctx->tokens, create_token(TOKEN_WORD, *ctx->acc));
	if (*ctx->acc)
		free(*ctx->acc);
	return (*ctx->tokens);
}
