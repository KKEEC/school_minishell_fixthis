/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:02:21 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:02:22 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"

void	handle_pipe(t_token **tokens)
{
	add_token(tokens, create_token(TOKEN_PIPE, "|"));
}

void	handle_heredoc(t_token **tokens, size_t *i)
{
	add_token(tokens, create_token(TOKEN_HEREDOC, "<<"));
	(*i)++;
}

void	handle_append(t_token **tokens, size_t *i)
{
	add_token(tokens, create_token(TOKEN_APPEND, ">>"));
	(*i)++;
}

void	handle_redirect_in(t_token **tokens)
{
	add_token(tokens, create_token(TOKEN_REDIR_IN, "<"));
}

void	handle_redirect_out(t_token **tokens)
{
	add_token(tokens, create_token(TOKEN_REDIR_OUT, ">"));
}
