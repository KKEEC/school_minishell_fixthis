/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plimbu <plimbu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:03:21 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:03:23 by plimbu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/tokenizer.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_status = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_signal_status = 131;
	
}

static void	execute_command_loop(t_env **env_list, int *status)
{
	t_ast	*ast;

	if (!env_list || !status)
		return ;
	while (1)
	{
		ast = handle_input(*env_list, status);
		if (g_signal_status)
		{
			*status = g_signal_status;
			g_signal_status = 0;
		}
		if (!ast)
			continue ;
		if (ast == (t_ast *)-1)
			continue ;
		if (ast == (t_ast *)-2)
		{
			*status = 2;
			continue ;
		}
		preprocess_heredocs(ast, *env_list);
		*status = execute_ast(ast, env_list);
		free_ast(ast);
		if (*status >= 128)
		{
			*status -= 128;
			break ;
		}
	}
}

void	minishell_loop(t_env *env_list, int *status)
{
	if (!status)
		return ;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	execute_command_loop(&env_list, status);
}
