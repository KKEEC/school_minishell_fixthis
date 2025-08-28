/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:47:11 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:47:13 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"
#include "../../../includes/utils.h"

t_ast	*new_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	node->args = NULL;
	node->redir_type = -1;
	node->filename = NULL;
	node->is_quoted_delimiter = 0;
	return (node);
}

static int	is_quoted_heredoc_delimiter(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len >= 2)
	{
		if ((filename[0] == '"' && filename[len - 1] == '"')
			|| (filename[0] == '\'' && filename[len - 1] == '\''))
			return (1);
	}
	if (len > 0 && filename[0] == '\\')
		return (1);
	return (0);
}

t_ast	*new_redir_node(int redir_type, const char *filename, t_ast *cmd)
{
	t_ast	*node;
	int		is_quoted;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	is_quoted = 0;
	if (redir_type == TOKEN_HEREDOC)
		is_quoted = is_quoted_heredoc_delimiter(filename);
	node->type = NODE_REDIR;
	node->redir_type = redir_type;
	node->filename = ft_strdup(filename);
	if (!node->filename)
	{
		free(node);
		return (NULL);
	}
	node->left = cmd;
	node->right = NULL;
	node->args = NULL;
	node->is_quoted_delimiter = is_quoted;
	return (node);
}

t_ast	*new_command_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->redir_type = 0;
	node->filename = NULL;
	node->is_quoted_delimiter = 0;
	return (node);
}
