/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:50:01 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:50:02 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sstr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	sstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!sstr)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			sstr[j] = s[i];
			j++;
		}
		i++;
	}
	sstr[j] = '\0';
	return (sstr);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dup;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	i = 0;
	while (str[len] && len < n)
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
