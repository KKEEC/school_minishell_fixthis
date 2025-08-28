/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:00:50 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/28 17:41:04 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/executor.h"
#include <stdio.h>
#include <unistd.h>  // pipe, dup, dup2, close, write
#include <string.h>  // strlen
#include <stdlib.h>  // free


int execute_heredoc(t_ast *ast, t_env **env_list)
{
	if (!ast || !env_list)
		return (1);
	int status = 0;
	char *str = read_heredoc_input(ast->filename, *env_list, &status);
	if (!str)
		return (1);

	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free(str);
		return (1);
	}

	// Write heredoc content to pipe, then close write end
	write(pipefd[1], str, ft_strlen(str));
	close(pipefd[1]);
	free(str);

	int saved_stdin = dup(0);
	if (saved_stdin == -1)
	{
		perror("dup");
		close(pipefd[0]);
		return (1);
	}
	if (dup2(pipefd[0], 0) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		close(saved_stdin);
		return (1);
	}
	close(pipefd[0]);

	// Remove heredoc argument if present (optional, depends on your AST structure)
	if (ast->left->args[1])
	{
		free(ast->left->args[1]);
		ast->left->args[1] = NULL;
	}

	status = execute_ast(ast->left, env_list);

	// Restore stdin
	dup2(saved_stdin, 0);
	close(saved_stdin);
	return (status);
}
