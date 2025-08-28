/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:01:31 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:01:32 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"
#include "../../../includes/utils.h"
#include <unistd.h>

void	write_pipe_in_error(t_token *token)
{
	if (token->next->next && token->next->next->type == TOKEN_PIPE)
		write(STDERR_FILENO, " syntax error near unexpected token `|'\n",
			39);
	else
		write(STDERR_FILENO, " syntax error near unexpected token `<'\n",
			39);
}

void	write_token_error(t_token *token)
{
	if (token->next->value)
	{
		write(STDERR_FILENO, " syntax error near unexpected token ", 36);
		write(STDERR_FILENO, "`", 1);
		write(STDERR_FILENO, token->next->value,
			ft_strlen(token->next->value));
		write(STDERR_FILENO, "'\n", 2);
	}
	else
		write(STDERR_FILENO, " syntax error near unexpected token `newline'\n",
			45);
}

int	handle_pipe_out_append_error(t_token *token)
{
	t_token	*check;

	check = token->next->next;
	if (check && check->type == TOKEN_WORD)
		return (0);
	if (check && check->type == TOKEN_APPEND)
	{
		write(STDERR_FILENO, " syntax error near unexpected token `>>'\n",
			40);
		return (1);
	}
	if (token->next->type == TOKEN_APPEND)
		write(STDERR_FILENO, " syntax error near unexpected token `>>'\n",
			40);
	else
		write(STDERR_FILENO,
			" syntax error near unexpected token `newline'\n", 45);
	return (1);
}

int	handle_pipe_redir_in_error(t_token *token)
{
	t_token	*check;

	check = token->next->next;
	if (check && check->type == TOKEN_WORD)
		return (0);
	if (check && check->type == TOKEN_PIPE)
		write(STDERR_FILENO, " syntax error near unexpected token `|'\n",
			39);
	else
		write(STDERR_FILENO, " syntax error near unexpected token `<'\n",
			39);
	return (1);
}

int	handle_pipe_redir_error(t_token *token)
{
	if (token->type == TOKEN_PIPE && (token->next->type == TOKEN_REDIR_OUT
			|| token->next->type == TOKEN_APPEND))
		return (handle_pipe_out_append_error(token));
	if (token->type == TOKEN_PIPE && token->next->type == TOKEN_REDIR_IN)
		return (handle_pipe_redir_in_error(token));
	return (-1);
}
