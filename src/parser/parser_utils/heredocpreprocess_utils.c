/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocpreprocess_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:00:00 by kkc               #+#    #+#             */
/*   Updated: 2025/08/29 18:33:39 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*heredoc_filename_prefix(int pid)
{
	char	*pid_str;
	char	*res;

	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (NULL);
	res = ft_strjoin("/tmp/minishell_heredoc_", pid_str);
	free(pid_str);
	return (res);
}

char	*heredoc_filename_suffix(char *prefix, int counter)
{
	char	*cnt_str;
	char	*tmp;
	char	*res;

	cnt_str = ft_itoa(counter);
	if (!cnt_str)
	{
		free(prefix);
		return (NULL);
	}
	tmp = join_and_free(prefix, "_");
	if (!tmp)
	{
		free(cnt_str);
		return (NULL);
	}
	res = join_and_free(tmp, cnt_str);
	free(cnt_str);
	return (res);
}
