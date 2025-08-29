/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:41:56 by kkc               #+#    #+#             */
/*   Updated: 2025/08/29 18:33:21 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include "../../../includes/tokenizer.h"

int	is_delimiter(const char *line, const char *delimiter)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	return (ft_strlen(line) == delimiter_len && ft_strcmp(line,
			delimiter) == 0);
}

char	*append_line_to_content(char *content, char *line)
{
	char	*temp;
	char	*new_content;

	temp = ft_strjoin(content, line);
	free(content);
	if (!temp)
		return (NULL);
	new_content = ft_strjoin(temp, "\n");
	free(temp);
	return (new_content);
}

static char	*init_heredoc_content(const char *delimiter, char **unquoted_delim)
{
	char	*content;

	*unquoted_delim = get_unquoted_delimiter(delimiter);
	if (!*unquoted_delim)
		return (NULL);
	content = ft_strdup("");
	if (!content)
	{
		free(*unquoted_delim);
		return (NULL);
	}
	return (content);
}

char	*read_heredoc_input(const char *delimiter, t_env *env_list, int *status)
{
	char	*content;
	char	*unquoted_delim;
	int		should_expand;

	should_expand = (env_list != NULL && !is_quoted_delimiter(delimiter));
	content = init_heredoc_content(delimiter, &unquoted_delim);
	if (!content)
		return (NULL);
	if (should_expand)
		content = read_heredoc_loop(content, unquoted_delim, env_list, status);
	else
		content = read_heredoc_loop(content, unquoted_delim, NULL, status);
	if (!content)
	{
		free(unquoted_delim);
		return (NULL);
	}
	free(unquoted_delim);
	return (content);
}
