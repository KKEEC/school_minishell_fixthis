/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:46:54 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:46:56 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/utils.h"

static int	process_token(t_ast **cmd, t_ast *command_node, t_token **tokens)
{
	if (is_redirection((*tokens)->type))
	{
		*cmd = handle_redirection_token(*cmd, tokens);
		if (!*cmd)
			return (0);
	}
	else if ((*tokens)->type == TOKEN_WORD)
	{
		if (!add_arg_to_command(command_node, (*tokens)->value))
			return (0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

t_ast	*parse_command_segment(t_token **tokens)
{
	t_ast	*cmd;
	t_ast	*command_node;

	if (!tokens)
		return (NULL);
	cmd = new_command_node();
	if (!cmd)
		return (NULL);
	command_node = cmd;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if (!process_token(&cmd, command_node, tokens))
		{
			free_ast(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

static t_ast	*handle_pipe_chain(t_ast *left, t_token **tokens)
{
	t_ast	*right;
	t_ast	*pipe_node;

	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_command_segment(tokens);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		pipe_node = new_pipe_node(left, right);
		if (!pipe_node)
		{
			free_ast(left);
			free_ast(right);
			return (NULL);
		}
		left = pipe_node;
	}
	return (left);
}

t_ast	*parse_tokens(t_token *tokens)
{
	t_ast	*left;

	if (!tokens)
		return (NULL);
	left = parse_command_segment(&tokens);
	if (!left)
		return (NULL);
	return (handle_pipe_chain(left, &tokens));
}
