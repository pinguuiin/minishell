/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:26:00 by donheo            #+#    #+#             */
/*   Updated: 2025/07/01 17:34:04 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

int		skip_spaces(const char *input, int i);
void	append_token(t_token **head, t_token *tail);
int		is_token_breaker(char c, int in_single_quote, int in_double_quote);
void	tokenize_elements(t_info *info);
t_token	*create_new_token(t_token_type type, t_info *info);

#endif
