/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:02:29 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:02:30 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"
#include "../../includes/env.h"

void	handle_spec_or_word(t_tokenize_ctx *ctx)
{
	if (ft_isschar(ctx->input[*ctx->i]))
		handle_special(ctx->input, ctx->i, ctx->tokens);
	else
		handle_word(ctx->input, ctx->i, ctx->tokens);
	(*ctx->i)++;
}

char	*handle_quotes(t_tokenize_ctx *ctx)
{
	if (ctx->input[*ctx->i] == '\'')
		return (handle_single_quote(ctx->input, ctx->i));
	else if (ctx->input[*ctx->i] == '"')
		return (handle_double_quote(ctx->input, ctx->i,
				ctx->env_list, ctx->status));
	return (NULL);
}

int	process_quoted_assignment(t_tokenize_ctx *ctx, char *quote)
{
	if (ctx->input[*ctx->i] == '=' && (ctx->input[*ctx->i + 1] == '"'
			|| ctx->input[*ctx->i + 1] == '\''))
	{
		*quote = ctx->input[*ctx->i + 1];
		*ctx->i += 2;
		while (ctx->input[*ctx->i] && ctx->input[*ctx->i] != *quote)
			(*ctx->i)++;
		if (ctx->input[*ctx->i] == *quote)
			(*ctx->i)++;
		return (1);
	}
	return (0);
}

char	*handle_normal_word(t_tokenize_ctx *ctx)
{
	size_t	start;
	char	*token_val;
	char	quote;
	char	*expanded_val;

	start = *ctx->i;
	while (ctx->input[*ctx->i] && !ft_isspace(ctx->input[*ctx->i])
		&& ctx->input[*ctx->i] != '\'' && ctx->input[*ctx->i] != '"'
		&& !ft_isschar(ctx->input[*ctx->i]))
	{
		if (process_quoted_assignment(ctx, &quote))
			break ;
		(*ctx->i)++;
	}
	token_val = ft_strndup(&ctx->input[start], *ctx->i - start);
	if (!token_val)
		return (NULL);
	expanded_val = expanddollar(token_val, ctx->env_list, ctx->status);
	free(token_val);
	return (expanded_val);
}
