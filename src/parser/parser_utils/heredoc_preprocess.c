/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:00:00 by kkc               #+#    #+#             */
/*   Updated: 2025/08/29 18:33:13 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/parser.h"
#include <fcntl.h>
#include <unistd.h>

static char	*build_heredoc_filename(int pid, int counter)
{
	char	*prefix;

	prefix = heredoc_filename_prefix(pid);
	if (!prefix)
		return (NULL);
	return (heredoc_filename_suffix(prefix, counter));
}

static char	*create_heredoc_tmpfile(const char *content, int *counter)
{
	char	*filename;
	int		fd;

	filename = build_heredoc_filename(getpid(), *counter);
	(*counter)++;
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (fd == -1)
	{
		free(filename);
		return (NULL);
	}
	if (write(fd, content, ft_strlen(content)) < 0)
	{
		close(fd);
		unlink(filename);
		free(filename);
		return (NULL);
	}
	close(fd);
	return (filename);
}

static void	handle_heredoc_node(t_ast *ast, t_env *env_list, int *counter)
{
	int		status;
	char	*content;

	status = 0;
	content = read_heredoc_input(ast->filename, env_list, &status);
	if (content)
	{
		ast->heredoc_tmpfile = create_heredoc_tmpfile(content, counter);
		free(content);
	}
	else
		ast->heredoc_tmpfile = NULL;
}

static void	preprocess_heredocs_rec(t_ast *ast, t_env *env_list, int *counter)
{
	if (!ast)
		return ;
	if (ast->type == NODE_REDIR && ast->redir_type == TOKEN_HEREDOC)
		handle_heredoc_node(ast, env_list, counter);
	preprocess_heredocs_rec(ast->left, env_list, counter);
	preprocess_heredocs_rec(ast->right, env_list, counter);
}

void	preprocess_heredocs(t_ast *ast, t_env *env_list)
{
	int	counter;

	counter = 0;
	preprocess_heredocs_rec(ast, env_list, &counter);
}
