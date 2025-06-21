/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:26:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 18:06:58 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// Type of redirection(<, >, >>, <<)
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

// Redirection node
typedef struct s_redir
{
	t_redir_type	type;// Type of redirection
	char			*file;// Target file or heredoc delimiter
	struct s_redir	*next;// Linked list for multiple redirections
}	t_redir;

// Command node (single command in a pipeline)
typedef struct s_cmd
{
	char			**argv;// NULL-terminated array of arguments
	t_redir			*redirection;// Linked list of input/output redirections
	bool			is_error;
	int				is_builtin;// Boolean flag for built-ins
	struct s_cmd	*next;// Next command in pipeline
}	t_cmd;

#endif
