/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:25:25 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 04:12:27 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Type of redirection(<, >, >>, <<)
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_HEREDOC_QUOTE,
	REDIR_AMB
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
	int				is_builtin;// Boolean flag for built-ins
	bool			is_error;
	struct s_cmd	*next;// Next command in pipeline
}	t_cmd;

#endif
