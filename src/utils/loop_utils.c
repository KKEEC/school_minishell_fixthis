/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:50:23 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 16:09:04 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/tokenizer.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

char	*get_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		return (NULL);
	if (*input == '\0')
	{
		free(input);
		return ((char *)-1);
	}
	add_history(input);
	return (input);
}

t_ast	*process_tokens(t_token *tokens, char *input)
{
	t_ast	*ast;

	if (!tokens || !input)
	{
		if (tokens)
			free_tokens(tokens);
		if (input)
			free(input);
		return (NULL);
	}
	if (is_syntax_error(tokens))
	{
		free_tokens(tokens);
		free(input);
		return ((t_ast *)-2);
	}
	ast = parse_tokens(tokens);
	free_tokens(tokens);
	free(input);
	if (!ast)
		return (NULL);
	return (ast);
}

t_ast	*handle_input(t_env *env_list, int *status)
{
	t_token	*tokens;
	char	*input;

	if (!status)
		return (NULL);
	input = get_input();
	if (!input)
		return (NULL);
	if (input == (char *)-1)
		return ((t_ast *)-1);
	tokens = tokenize(input, env_list, status);
	if (!tokens)
	{
		free(input);
		return (NULL);
	}
	return (process_tokens(tokens, input));
}
