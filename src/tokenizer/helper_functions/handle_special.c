/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:02:01 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:02:02 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"

void	handle_special(const char *input, size_t *i, t_token **tokens)
{
	if (input[*i] == '|')
		add_token(tokens, create_token(TOKEN_PIPE, "|"));
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, create_token(TOKEN_HEREDOC, "<<"));
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, create_token(TOKEN_APPEND, ">>"));
		(*i)++;
	}
	else if (input[*i] == '<')
		add_token(tokens, create_token(TOKEN_REDIR_IN, "<"));
	else if (input[*i] == '>')
		add_token(tokens, create_token(TOKEN_REDIR_OUT, ">"));
}
