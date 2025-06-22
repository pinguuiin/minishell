/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:26:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 14:18:47 by donheo           ###   ########.fr       */
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
	int	has_env;
	int	has_word;
}	t_cmd_type


#endif
