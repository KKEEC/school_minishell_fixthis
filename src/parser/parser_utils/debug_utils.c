/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:47:16 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:47:17 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../includes/parser.h"

void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

static void	print_command_node(t_ast *node)
{
	int	i;

	printf("COMMAND: ");
	i = 0;
	while (node->args && node->args[i])
	{
		printf("%s ", node->args[i]);
		i++;
	}
	printf("\n");
}

static void	print_redir_node(t_ast *node, int depth)
{
	printf("REDIRECTION: ");
	if (node->redir_type == TOKEN_REDIR_IN)
		printf("< ");
	else if (node->redir_type == TOKEN_REDIR_OUT)
		printf("> ");
	else if (node->redir_type == TOKEN_APPEND)
		printf(">> ");
	else if (node->redir_type == TOKEN_HEREDOC)
		printf("<< ");
	printf("file: %s\n", node->filename);
	print_ast(node->left, depth + 1);
}

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_COMMAND)
		print_command_node(node);
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == NODE_REDIR)
		print_redir_node(node, depth);
}
