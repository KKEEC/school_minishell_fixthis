/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:55:36 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:10:59 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

// Type definitions for node type and abstract syntax tree

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR,
}					t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	t_token_type	redir_type;
	char			*filename;
	int				is_quoted_delimiter;
	char			*heredoc_tmpfile; // path to heredoc temp file (if any)
}					t_ast;

// core parser fucntions that returns abstract syntax tree

t_ast				*parse_tokens(t_token *tokens);
t_ast				*parse_command_segment(t_token **tokens);


// Heredoc preprocessing
void preprocess_heredocs(t_ast *ast, t_env *env_list);
// AST node constructor functions

t_ast				*new_command_node(void);
t_ast				*new_pipe_node(t_ast *left, t_ast *right);
t_ast				*new_redir_node(int redir_type, const char *filename,
						t_ast *cmd);

// Parser utilities functions

int					add_arg_to_command(t_ast *cmd, const char *arg);
t_ast				*handle_redirection_token(t_ast *cmd, t_token **tokens);
int					is_syntax_error(t_token *token);
int					is_redirection(t_token_type type);

// syntax error handling codes

int					handle_pipe_redir_error(t_token *token);
void				write_token_error(t_token *token);
void				write_pipe_in_error(t_token *token);

// debug function to print ast tree                              

void				print_indent(int depth);
void				print_ast(t_ast *node, int depth);

// free AST node function

void				free_ast(t_ast *node);

// handling input functions

char				*get_input(void);
t_ast				*process_tokens(t_token *tokens, char *input);
t_ast				*handle_input(t_env *env_list, int *status);

//preprocess for heredoc
char	*join_and_free(char *s1, char *s2);
char	*heredoc_filename_prefix(int pid);
char	*heredoc_filename_suffix(char *prefix, int counter);

#endif