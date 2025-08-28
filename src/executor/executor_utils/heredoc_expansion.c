/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:42:01 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:42:02 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/executor.h"
#include "../../../includes/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	*expand_and_append_line(char *content, char *line,
	t_env *env_list, int *status)
{
	char	*expanded_line;

	expanded_line = expanddollar(line, env_list, status);
	content = append_line_to_content(content, expanded_line);
	free(expanded_line);
	return (content);
}

char	*read_heredoc_loop(char *content, const char *unquoted_delim,
	t_env *env_list, int *status)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || is_delimiter(line, unquoted_delim))
		{
			free(line);
			break ;
		}
		if (env_list)
			content = expand_and_append_line(content, line, env_list, status);
		else
			content = append_line_to_content(content, line);
		free(line);
		if (!content)
			return (NULL);
	}
	return (content);
}

int	is_quoted_delimiter(const char *delimiter)
{
	size_t	len;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len < 1)
		return (0);
	if (delimiter[0] == '\\')
		return (1);
	if (len < 2)
		return (0);
	if ((delimiter[0] == '"' && delimiter[len - 1] == '"')
		|| (delimiter[0] == '\'' && delimiter[len - 1] == '\''))
		return (1);
	return (0);
}

char	*get_unquoted_delimiter(const char *delimiter)
{
	size_t	len;
	char	*unquoted;

	if (!delimiter)
		return (NULL);
	len = ft_strlen(delimiter);
	if (len > 0 && delimiter[0] == '\\')
		return (ft_strdup(delimiter + 1));
	if (!is_quoted_delimiter(delimiter))
		return (ft_strdup(delimiter));
	unquoted = malloc(len - 1);
	if (!unquoted)
		return (NULL);
	ft_strcpy(unquoted, delimiter + 1);
	unquoted[len - 2] = '\0';
	return (unquoted);
}
