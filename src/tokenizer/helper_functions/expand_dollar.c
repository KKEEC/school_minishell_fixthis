/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:49:15 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:49:16 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"

char	*expanddollar(const char *str, t_env *env_list, int *status)
{
	char	*result;
	char	*temp;
	char	*tstr;

	tstr = (char *)str;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*tstr)
	{
		if (*tstr == '$')
		{
			temp = handle_dollar(result, &tstr, status, env_list);
			free(result);
			result = temp;
		}
		else
		{
			temp = append_char(result, *tstr);
			free(result);
			result = temp;
			tstr++;
		}
	}
	return (result);
}
