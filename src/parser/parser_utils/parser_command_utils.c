/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:47:39 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:47:46 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"
#include "../../../includes/utils.h"

static int	copy_existing_args(char **new_args, char **old_args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_args[i] = old_args[i];
		i++;
	}
	return (i);
}

int	add_arg_to_command(t_ast *cmd, const char *arg)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (0);
	i = copy_existing_args(new_args, cmd->args, count);
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		return (0);
	}
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

t_ast	*handle_redirection_token(t_ast *cmd, t_token **tokens)
{
	int		redir_type;
	char	*filename;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	filename = (*tokens)->value;
	*tokens = (*tokens)->next;
	return (new_redir_node(redir_type, filename, cmd));
}
