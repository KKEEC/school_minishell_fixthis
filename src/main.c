/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:03:26 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:03:39 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"
#include "../includes/env.h"
#include <unistd.h>
#include <stdlib.h>

static void	init_pwd(t_env **env_list)
{
	char	*cwd;

	if (!env_list)
		return ;
	if (!get_env_value(*env_list, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			update_env(env_list, "PWD", cwd);
			free(cwd);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		status;

	(void)argc;
	(void)argv;
	env_list = NULL;
	status = 0;
	env_list = init_env_list(envp, &env_list);
	if (!env_list)
	{
		write(STDERR_FILENO, "Environment initialization failed\n", 35);
		return (1);
	}
	init_pwd(&env_list);
	minishell_loop(env_list, &status);
	if (env_list)
		free_env_list(env_list);
	rl_clear_history();
	return (status);
}
