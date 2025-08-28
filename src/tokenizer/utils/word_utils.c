/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:48:39 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:48:40 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/tokenizer.h"
#include "../../../includes/env.h"

char	*process_dollar_char(char *result, char **tstr, int *status,
	t_env *env_list)
{
	char	*temp;

	temp = handle_dollar(result, tstr, status, env_list);
	return (temp);
}

char	*process_normal_char(char *result, char **tstr)
{
	char	*temp;

	temp = append_char(result, **tstr);
	(*tstr)++;
	return (temp);
}
