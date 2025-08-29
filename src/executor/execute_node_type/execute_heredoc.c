/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:00:50 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/29 21:37:41 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include <fcntl.h> // open, O_CREAT, O_EXCL, O_RDWR
#include <stdio.h>
#include <stdlib.h> // free
#include <string.h> // strlen
#include <unistd.h> // pipe, dup, dup2, close, write

// Remove heredoc argument if present (optional, depends on your AST structure)
// Restore stdin
// Temp file cleanup should be handled after execution
// (e.g.,in free_ast or main loop)
//fprintf(stderr, "heredoc: temp file not set\n");

int	execute_heredoc(t_ast *ast, t_env **env_list)
{
	int	tmpfd;
	int	saved_stdin;
	int	status;

	if (!ast || !env_list)
		return (1);
	if (!ast->heredoc_tmpfile)
		return (write(2, "heredoc: temp file not set\n", 27), 1);
	tmpfd = open(ast->heredoc_tmpfile, O_RDONLY);
	if (tmpfd == -1)
		return (perror("open heredoc tmpfile"), 1);
	saved_stdin = dup(0);
	if (saved_stdin == -1)
		return (perror("dup"), close(tmpfd), 1);
	if (dup2(tmpfd, 0) == -1)
		return (perror("dup2"), close(tmpfd), close(saved_stdin), 1);
	close(tmpfd);
	if (ast->left && ast->left->args && ast->left->args[1])
	{
		free(ast->left->args[1]);
		ast->left->args[1] = NULL;
	}
	status = execute_ast(ast->left, env_list);
	dup2(saved_stdin, 0);
	return (close(saved_stdin), status);
}
