/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:24:16 by kkc               #+#    #+#             */
/*   Updated: 2025/08/27 15:24:17 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executor.h"
#include <unistd.h>
#include <stdio.h>

int	builtin_pwd(void)
{
	char	*currentdir;

	currentdir = getcwd(NULL, 0);
	if (!currentdir)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", currentdir);
	free(currentdir);
	return (0);
}
