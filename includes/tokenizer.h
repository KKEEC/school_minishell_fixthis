/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkc <kkc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:55:32 by plimbu            #+#    #+#             */
/*   Updated: 2025/08/27 16:16:14 by kkc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "env.h"
# include "utils.h"

//type definitions for 
//token type, tokens chaining and context struct for less argument reduction

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_tokenize_ctx
{
	const char		*input;
	size_t			*i;
	char			**acc;
	t_token			**tokens;
	t_env			*env_list;
	int				*status;
}					t_tokenize_ctx;

// tokeniser core functions

t_token				*tokenize(const char *input, t_env *env_list, int *status);
t_token				*finalize_tokenization(t_tokenize_ctx *ctx);

//token utility functions

void				free_tokens(t_token *head);
t_token				*create_token(t_token_type type, const char *input);
void				add_token(t_token **head, t_token *new_token);
int					is_operator(t_token_type type);

//processing string functions

char				*ft_itoa(int n);
char				*append_char(char *result, char c);
char				*append_pid(char *result);
char				*append_status(char *result, int *status);
char				*append_var(char *result, char **tstr, t_env *env_list);
char				*handle_dollar(char *result, char **tstr, int *status,
						t_env *env_list);
char				*process_dollar_char(char *result, char **tstr, int *status,
						t_env *env_list);
char				*process_normal_char(char *result, char **tstr);
char				*expanddollar(const char *str, t_env *env_list,
						int *status);

// Core functions to handle special symbols like redir, pipe and quotes

void				handle_special(const char *input, size_t *i,
						t_token **tokens);
int					handle_word(const char *input, size_t *i, t_token **tokens);
char				*handle_single_quote(const char *input, size_t *i);
char				*handle_double_quote(const char *input, size_t *i,
						t_env *env_list, int *status);
char				*handle_quoted_esc_chars(const char *src, size_t len);
char				*handle_unquoted_esc_chars(const char *src, size_t len);

//tokeniser utilities functions for quotes and other core fucntions

void				handle_whitespace(t_tokenize_ctx *ctx);
int					handle_word_accumulation(t_tokenize_ctx *ctx);
int					handle_quote_accumulation(t_tokenize_ctx *ctx);
void				handle_special_finalize(t_tokenize_ctx *ctx);
void				handle_spec_or_word(t_tokenize_ctx *ctx);
char				*handle_quotes(t_tokenize_ctx *ctx);
char				*handle_normal_word(t_tokenize_ctx *ctx);
int					process_quoted_assignment(t_tokenize_ctx *ctx, char *quote);
void				process_character(t_tokenize_ctx *ctx);
void				tokenize_loop(t_tokenize_ctx *ctx);

#endif
