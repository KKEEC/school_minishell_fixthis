/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:41:35 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:41:36 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/utils.h"

void	copy_value(char *value, int *i, int val_len, char *temp)
{
	int	j;

	j = 0;
	while (value[*i] && *i < val_len - 1)
	{
		temp[j] = value[*i];
		(*i)++;
		j++;
	}
	temp[j] = '\0';
}

char	*trimquotes(char *value)
{
	int		i;
	char	*temp;
	int		new_len;
	int		val_len;

	if (!value)
		return (NULL);
	i = 0;
	val_len = (int)ft_strlen(value);
	if ((value[0] == '"' && value[val_len - 1] == '"')
		|| (value[0] == '\'' && value[val_len - 1] == '\''))
	{
		new_len = val_len - 2;
		i = 1;
	}
	else
		return (value);
	temp = malloc(new_len + 1);
	copy_value(value, &i, val_len, temp);
	return (temp);
}
