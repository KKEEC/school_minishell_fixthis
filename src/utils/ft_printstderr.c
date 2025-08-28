/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstderr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:02:46 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:02:47 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_printstderr(const char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}
