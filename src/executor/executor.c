/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:41:22 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:41:24 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/minishell.h"
#include <stdio.h>

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (isstrequal(cmd, "echo")
		|| isstrequal(cmd, "cd")
		|| isstrequal(cmd, "pwd")
		|| isstrequal(cmd, "export")
		|| isstrequal(cmd, "unset")
		|| isstrequal(cmd, "env")
		|| isstrequal(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	execute_builtin(t_ast *node, t_env **env_list)
{
	char	**args;
	int		status;

	if (!node || !node->args || !node->args[0])
		return (1);
	args = node->args;
	status = 0;
	if (isstrequal(args[0], "echo"))
		status = builtin_echo(args);
	else if (isstrequal(args[0], "pwd"))
		status = builtin_pwd();
	else if (isstrequal(args[0], "cd"))
		status = builtin_cd(args, *env_list);
	else if (isstrequal(args[0], "env"))
		status = builtin_env(*env_list, args);
	else if (isstrequal(args[0], "export"))
		status = builtin_export(args, env_list);
	else if (isstrequal(args[0], "unset"))
		status = builtin_unset(args, env_list);
	else if (isstrequal(args[0], "exit"))
		status = builtin_exit(args);
	return (status);
}

void	execute_command_node(t_ast *ast, t_env **env_list, int *status)
{
	if (!ast || !ast->args || !ast->args[0] || !status)
		return ;
	if (is_builtin(ast->args[0]))
		*status = execute_builtin(ast, env_list);
	else
		*status = execute_commands(ast, env_list);
}

static int	execute_redirection(t_ast *ast, t_env **env_list)
{
	if (!ast || !env_list)
		return (1);
	if (ast->redir_type == TOKEN_REDIR_IN)
		return (execute_redirin(ast, env_list));
	else if (ast->redir_type == TOKEN_REDIR_OUT)
		return (execute_redirout(ast, env_list));
	else if (ast->redir_type == TOKEN_APPEND)
		return (execute_append(ast, env_list));
	else if (ast->redir_type == TOKEN_HEREDOC)
		return (execute_heredoc(ast, env_list));
	else
		return (1);
}

int	execute_ast(t_ast *ast, t_env **env_list)
{
	int	status;

	status = 0;
	if (!ast)
		return (0);
	if (!env_list)
		return (1);
	if (ast->type == NODE_COMMAND)
	{
		if (!ast->args || !ast->args[0])
			return (0);
		execute_command_node(ast, env_list, &status);
	}
	else if (ast->type == NODE_REDIR)
		status = execute_redirection(ast, env_list);
	else if (ast->type == NODE_PIPE)
		status = execute_pipe(ast, env_list);
	else
		status = 1;
	return (status);
}
