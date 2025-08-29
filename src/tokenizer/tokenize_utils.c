/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:48:22 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:48:26 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../includes/env.h"

void	handle_whitespace(t_tokenize_ctx *ctx)
{
	if (*ctx->acc && (*ctx->acc)[0] != '\0')
		add_token(ctx->tokens, create_token(TOKEN_WORD, *ctx->acc));
	if (*ctx->acc)
	{
		free(*ctx->acc);
		*ctx->acc = NULL;
	}
	(*ctx->i)++;
}

int	handle_word_accumulation(t_tokenize_ctx *ctx)
{
	char	*part;
	char	*old_acc;

	part = handle_normal_word(ctx);
	if (!part)
	{
		free(*ctx->acc);
		free_tokens(*ctx->tokens);
		return (0);
	}
	old_acc = *ctx->acc;
	if (*ctx->acc)
		*ctx->acc = ft_strjoin(*ctx->acc, part);
	else
		*ctx->acc = ft_strdup(part);
	if (!*ctx->acc)
	{
		free(old_acc);
		free(part);
		free_tokens(*ctx->tokens);
		return (0);
	}
	free(old_acc);
	free(part);
	return (1);
}

int	handle_quote_accumulation(t_tokenize_ctx *ctx)
{
	char	*part;
	char	*old_acc;

	part = handle_quotes(ctx);
	if (!part)
	{
		if(*ctx->acc)
		{
			free(*ctx->acc);
			*ctx->acc = NULL;
		}
		free_tokens(*ctx->tokens);
		*ctx->tokens = NULL;
		return (0);
	}
	old_acc = *ctx->acc;
	if (*ctx->acc)
		*ctx->acc = ft_strjoin(*ctx->acc, part);
	else
		*ctx->acc = ft_strdup(part);
	if (!*ctx->acc)
	{
		free(old_acc);
		free(part);
		free_tokens(*ctx->tokens);
		return (0);
	}
	free(old_acc);
	free(part);
	return (1);
}

void	handle_special_finalize(t_tokenize_ctx *ctx)
{
	if (*ctx->acc && (*ctx->acc)[0] != '\0')
		add_token(ctx->tokens, create_token(TOKEN_WORD, *ctx->acc));
	if (*ctx->acc)
	{
		free(*ctx->acc);
		*ctx->acc = NULL;
	}
	handle_spec_or_word(ctx);
}
