/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:26:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/23 09:14:35 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


typedef	enum e_token_type
{
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	WORD,
	ENV_VAR,
	WORD_WITH_ENV,
}	t_token_type;

typedef	struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd_type
{
	int	start_i;
	int	end_i;
	int	in_single_quote;
	int	in_double_quote;
	int	i;
	int	has_env;
	int	has_word;
}	t_cmd_type;

int		tokenize_input(const char *input, int i, t_info *info);
int		tokenize_output(const char *input, int i, t_info *info);
int		tokenize_pipe(int i, t_info *info);
int		tokenize_cmd(const char *input, int i, t_info *info);
void	tokenize_elements(const char *input);

int		skip_spaces(const char *input, int i);
void	connect_tokens(t_token **head, t_token *tail);
int		skip_env_name(const char *input, t_cmd_type *cmd_type);
void	set_quote_and_word(int *quote_flag, t_cmd_type *cmd_type);
int		is_token_boundary(char c, t_cmd_type cmd_type);

#endif
