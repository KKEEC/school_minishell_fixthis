/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:49:06 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:49:08 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"
#include <unistd.h>

char	*append_char(char *result, char c)
{
	char	buff[2];
	char	*tmp;

	buff[0] = c;
	buff[1] = '\0';
	tmp = ft_strjoin(result, buff);
	return (tmp);
}

char	*append_pid(char *result)
{
	char	*pid_str;
	char	*tmp;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (ft_strdup(result));
	tmp = ft_strjoin(result, pid_str);
	free(pid_str);
	return (tmp);
}

char	*append_status(char *result, int *status)
{
	char	*status_str;
	char	*tmp;

	status_str = ft_itoa(*status);
	if (!status_str)
		return (ft_strdup(result));
	tmp = ft_strjoin(result, status_str);
	free(status_str);
	return (tmp);
}
