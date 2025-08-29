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
#include <fcntl.h>   // open, O_CREAT, O_EXCL, O_RDWR


int execute_heredoc(t_ast *ast, t_env **env_list)
{
	if (!ast || !env_list)
		return (1);

	   if (!ast->heredoc_tmpfile)
	   {
			   fprintf(stderr, "heredoc: temp file not set\n");
			   return (1);
	   }
	   int tmpfd = open(ast->heredoc_tmpfile, O_RDONLY);
	   if (tmpfd == -1)
	   {
			   perror("open heredoc tmpfile");
			   return (1);
	   }

	   int saved_stdin = dup(0);
	   if (saved_stdin == -1)
	   {
			   perror("dup");
			   close(tmpfd);
			   return (1);
	   }
	   if (dup2(tmpfd, 0) == -1)
	   {
			   perror("dup2");
			   close(tmpfd);
			   close(saved_stdin);
			   return (1);
	   }
	   close(tmpfd);

	   // Remove heredoc argument if present (optional, depends on your AST structure)
	   if (ast->left && ast->left->args && ast->left->args[1])
	   {
			   free(ast->left->args[1]);
			   ast->left->args[1] = NULL;
	   }

	   int status = execute_ast(ast->left, env_list);

	   // Restore stdin
	   dup2(saved_stdin, 0);
	   close(saved_stdin);
	   // Temp file cleanup should be handled after execution (e.g., in free_ast or main loop)
	   return (status);
}
