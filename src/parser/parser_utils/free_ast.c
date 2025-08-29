/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:47:22 by kkc               #+#    #+#             */
/*   Updated: 2025/08/29 21:20:51 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"
#include <unistd.h>

static void	free_command_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

static void	free_redirection(t_ast *node)
{
	if (node->filename)
		free(node->filename);
	if (node->redir_type == TOKEN_HEREDOC && node->heredoc_tmpfile)
	{
		unlink(node->heredoc_tmpfile);
		free(node->heredoc_tmpfile);
	}
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND)
		free_command_args(node->args);
	else if (node->type == NODE_REDIR)
		free_redirection(node);
	free(node);
}

/* void	free_ast(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND && node->args)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->type == NODE_REDIR)
	{
		if (node->filename)
			free(node->filename);
		if (node->redir_type == TOKEN_HEREDOC && node->heredoc_tmpfile)
		{
			unlink(node->heredoc_tmpfile);
			free(node->heredoc_tmpfile);
		}
	}
	free(node);
	node = NULL;
} */
