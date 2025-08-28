/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:01:36 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:01:38 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"
#include "../../../includes/utils.h"
#include <unistd.h>

static int	process_token_loop(t_token **token)
{
	int	check_result;

	while (*token && (*token)->next)
	{
		if (is_operator((*token)->type))
		{
			if ((*token)->next->type != TOKEN_WORD)
			{
				check_result = handle_pipe_redir_error(*token);
				if (check_result == 1)
					return (1);
				if (check_result == 0)
				{
					*token = (*token)->next;
					continue ;
				}
				write_token_error(*token);
				return (1);
			}
		}
		*token = (*token)->next;
	}
	return (0);
}

int	is_syntax_error(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_PIPE)
	{
		write(STDERR_FILENO, " syntax error near unexpected token `|'\n", 39);
		return (1);
	}
	if (process_token_loop(&token) == 1)
		return (1);
	if (token && is_operator(token->type))
	{
		write(STDERR_FILENO,
			" syntax error near unexpected token `newline'\n", 45);
		return (1);
	}
	return (0);
}
